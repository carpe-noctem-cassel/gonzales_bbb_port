#ifndef PROXY_H_
#define PROXY_H_

#include <exception>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdio.h>
#include <string>
#include <unistd.h>

#include <arpa/inet.h>
#include <net/if.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/time.h>

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include <spdlog/spdlog.h>

#include <msl_actuator_msgs/RawOdometryInfo.h>
#include <msl_actuator_msgs/MotionControl.h>

using boost::asio::ip::udp;
using boost::asio::ip::address;

constexpr size_t BUFSIZE = 64000;

using msl_actuator_msgs::RawOdometryInfo;
using msl_msgs::MotionInfo;

// TODO: Rename Class
class Proxy {
  public:
	Proxy(const std::string& multicast_address, unsigned short port);
	~Proxy();

	void sendOdometry(const RawOdometryInfo& msg);

	void listen();
	void handle_packet(const boost::system::error_code& error,
	                   std::size_t bytes_transferred);
	void run_udp();
	MotionInfo* get_motion();

  private:
	boost::asio::io_service service;
	std::unique_ptr<udp::socket> socket;
	udp::endpoint listen_endpoint;
	udp::endpoint peer_endpoint;
	boost::array<uint8_t, BUFSIZE> recv_buffer;
	boost::array<uint8_t, BUFSIZE> send_buffer;

	std::shared_ptr<spdlog::logger> logger;
	MotionInfo current_command;
	struct timeval last_cmd_received;
};

#endif /* PROXY_H_ */
