#include "Proxy.h"

#include <ros/serialization.h>
#include <string>
#include <utils.h>

#include <spdlog/fmt/ostr.h>

#include <msl_actuator_msgs/MotionControl.h>

using boost::asio::ip::udp;

/**
 * This flag enables reuse_addr and loopback, which makes it to send/receive
 * the multicast traffic from the same machine.
 * */
constexpr bool NETWORK_DEBUG = true;

Proxy::Proxy(const std::string& multicast_address, unsigned short port) {
	const auto mc_address = boost::asio::ip::address::from_string(multicast_address);
	listen_endpoint = udp::endpoint(mc_address, port);

	logger = spdlog::get("logger");
	logger->debug("opening socket to {}", multicast_address);
	socket = std::unique_ptr<udp::socket>(new udp::socket(service));

	socket->open(listen_endpoint.protocol());
	if (NETWORK_DEBUG)
		socket->set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	socket->bind(listen_endpoint);
	socket->set_option(boost::asio::ip::multicast::enable_loopback(NETWORK_DEBUG));
	socket->set_option(boost::asio::ip::multicast::join_group(mc_address));

	listen();
	logger->debug("udp connection setup done");
}

Proxy::~Proxy() { service.stop(); }

void
Proxy::sendOdometry(const RawOdometryInfo& msg) {
	const auto msg_size = ros::serialization::serializationLength(msg);
	const auto total_size = msg_size + sizeof(uint32_t);
	if (total_size > BUFSIZE) {
		/* TODO: Exception */
		return;
	}

	try {
		ros::serialization::OStream stream(send_buffer.data() + sizeof(uint32_t),
		                                   msg_size);

		*((uint32_t*)send_buffer.data()) = topic_hash("/RawOdometry");
		ros::serialization::serialize(stream, msg);

		socket->send_to(boost::asio::buffer(send_buffer, total_size), listen_endpoint);
	} catch (const std::exception& e) {
	}
}

void
Proxy::listen() {
	socket->async_receive_from(boost::asio::buffer(recv_buffer), peer_endpoint,
	                           boost::bind(&Proxy::handle_packet, this,
	                                       boost::asio::placeholders::error,
	                                       boost::asio::placeholders::bytes_transferred));
}

void
Proxy::handle_packet(const boost::system::error_code& error,
                     std::size_t bytes_transferred) {
	logger->trace("received udp message from {}", peer_endpoint);
	if (bytes_transferred > BUFSIZE) {
		logger->warn("udp message of size {} ignored, because its larger than {}",
		             bytes_transferred, BUFSIZE);
		return;
	}

	if (error) {
		logger->error("error receiving udp packet: {}", error);
		return;
	}

	uint32_t id = *((uint32_t*)(recv_buffer.data()));
	logger->trace("udp packet id: {}", id);
	try {
		ros::serialization::IStream stream(((uint8_t*)recv_buffer.data()) +
		                                       sizeof(uint32_t),
		                                   bytes_transferred - sizeof(uint32_t));

		switch (id) {
		case topic_hash("MotionControl"): {
			using msl_actuator_msgs::MotionControl;
			MotionControl mc;
			ros::serialization::Serializer<MotionControl>::read(stream, mc);
			gettimeofday(&last_cmd_received, NULL);
			current_command = mc.motion;
		} break;
		default:
			logger->trace("udp packet with id {} was ignored/not handled", id);
			break;
		}
	} catch (const std::exception& e) {
		logger->error("error while deserializing message: {}", e.what());
	}

	listen();
	return;
}

#define TIMEDIFFMS(n, o)                                                                 \
	((n).tv_sec - (o).tv_sec) * 1000 + ((n).tv_usec - (o).tv_usec) / 1000
#include <settings.h>
extern controller_settings current_settings;

MotionInfo*
Proxy::get_motion() {
	static struct timeval cur_time;
	gettimeofday(&cur_time, NULL);
	if (TIMEDIFFMS(cur_time, last_cmd_received) > current_settings.commandTimeout) {

		// std::cout << "Time diff to large: last:" << last_cmd_received.tv_sec << "
		// " << last_cmd_received.tv_usec << " cur: " << cur_time.tv_sec << " " <<
		// cur_time.tv_usec << std::endl;
		return nullptr;
	}
	return &current_command;
}

void
Proxy::run_udp() {
	service.poll();
}
