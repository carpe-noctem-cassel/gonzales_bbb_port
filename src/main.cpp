#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <spdlog/spdlog.h>

#include "driver/eposcan.h"
#include <udpcanconnection.h>
#include <usbcanconnection.h>

#include "gonzales.h"
#include "logging.h"
#include "settings.h"

#include <string>

#include <Proxy.h>

#include <Configuration.h>
#include <SystemConfig.h>

#include <getopt.h>
#define CONTROLLER_COUNT 4

using namespace msl_msgs;
using namespace std;
extern gonzales_state gonz_state;

void
print_usage(const char* prog_name) {
	printf("usage: %s [-i can_interface] [-m multicast_address] [-l] [-v [-v]] \n", prog_name);
}

struct ProgramOptions {
	std::string can_interface = "can0";
	std::string multicast_address = "226.16.32.40";
	unsigned short multicast_port = 59873;
	spdlog::level::level_enum log_level = spdlog::level::warn;
	bool logging_enabled = false;
};

ProgramOptions
parse_options(int argc, char* argv[]) {
	ProgramOptions opts;

	int c;
	// TODO: Revise config using yaml or systemconfig?
	while ((c = getopt(argc, argv, "i:hsvlm:")) != -1)
		switch (c) {
		case 'i':
			opts.can_interface = std::string(optarg);
			break;
		case 'm':
			opts.multicast_address = std::string(optarg);
			break;
		case 'l':
			opts.logging_enabled = true;
			break;
		case 'v':
			if (opts.log_level == spdlog::level::debug)
				opts.log_level = spdlog::level::trace;
			else
				opts.log_level = spdlog::level::debug;
			break;
		case 'h':
			print_usage(argv[0]);
			exit(1);
		default:;
		}

	return opts;
}

struct timeval time_last;
struct timeval time_cur;

Controlling::EposCan* ep;

Proxy* proxy;

int
main(int argc, char** argv) {
	const auto opts = parse_options(argc, argv);
	auto console = spdlog::stdout_logger_mt("logger");
	console->set_level(opts.log_level);
	console->trace("log level set to: {}", opts.log_level);

	if (opts.logging_enabled) {
		console->trace("motion logging enabled");
	}

	settings_init();

	UsbCanConnection* cc = new UsbCanConnection(opts.can_interface.c_str());
	ep = new Controlling::EposCan(CONTROLLER_COUNT, cc);

	gonz_init(); // init main controller

	try {
		proxy = new Proxy(opts.multicast_address, opts.multicast_port);
	} catch (const std::exception& e) {
		console->error("network/udp error: {}", e.what());
		exit(-1);
	}

	cc->Start();
	usleep(30000);

	while (ep->InitAllNodes() <= 0) {
		std::cout << "Could not initialise all controllers! Retrying...\n";
		usleep(500000);
	};

	gonz_state.currentMotionGoal.x = 0;
	gonz_state.currentMotionGoal.y = 0;
	gonz_state.currentMotionGoal.rotation = 0;

	console->trace("Starting motion loop...");
	while (true) {
		MotionInfo* cmd;
		gettimeofday(&time_last, NULL);

		proxy->run_udp();
		cmd = proxy->get_motion();
		if (cmd != nullptr) {
			console->trace("Got motion command!");
			gonz_set_motion_request((cmd)->angle, (cmd)->translation, (cmd)->rotation);
			gonz_main();
		} else {
			gonz_idle();
		}

		// Log to stdout if enabled
		if (opts.logging_enabled)
			logData(stdout);

		// Sleep to save processing time
		gettimeofday(&time_cur, NULL);
		usleep(max(
		    10l, (current_settings.controllerLoopTime - TIMEDIFFMS(time_cur, time_last)) *
		             1000l));
	}

	return 0;
}
