#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include <spdlog/spdlog.h>

#include "driver/eposcan.h"
#include <udpcanconnection.h>
#include <usbcanconnection.h>

#include "settings.h"
#include "gonzales.h"
#include "logging.h"

#include <string>

#include <Proxy.h>

#include <SystemConfig.h>
#include <Configuration.h>

#include <getopt.h>
#define CONTROLLER_COUNT 4

using namespace msl_msgs;
using namespace std;
extern gonzales_state gonz_state;


void
print_usage(const char* prog_name) {
	printf("usage: %s [-i can_interface] [-v [-v]] \n", prog_name);
}

struct ProgramOptions {
	std::string can_interface = "can0";
	std::string multicast_address = "224.16.32.40";
	unsigned short multicast_port = 59873;
	spdlog::level::level_enum log_level = spdlog::level::warn;
};

ProgramOptions
parse_options(int argc, char* argv[]) {
	ProgramOptions opts;

	int c;
	// TODO: Revise config using yaml or systemconfig?
	while ((c = getopt(argc, argv, "i:hsv")) != -1)
		switch (c) {
		case 'i':
			opts.can_interface = std::string(optarg);
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

int main(int argc, char** argv) {
	const auto opts = parse_options(argc, argv);
	auto console = spdlog::stdout_logger_mt("logger");
	console->set_level(opts.log_level);
	settings_init();

	UsbCanConnection* cc = new UsbCanConnection(opts.can_interface.c_str());
	ep = new Controlling::EposCan(CONTROLLER_COUNT,cc);

	gonz_init(); //init main controller
    logging_init();

	Proxy* proxy;
	try {
		proxy = new Proxy(opts.multicast_address, opts.multicast_port);
	} catch (const std::exception& e) {
		console->error("network/udp error: {}", e.what());
		exit(-1);
	}

	cc->Start();
	usleep(30000);

	while(ep->InitAllNodes()<=0) {
        std::cout << "Could not initialise all controllers! Retrying...\n";
		usleep(500000);
	};

    gonz_state.currentMotionGoal.x = 0;
    gonz_state.currentMotionGoal.y = 0;
    gonz_state.currentMotionGoal.rotation = 0;

	while(true) {
		MotionInfo* cmd;
		gettimeofday(&time_last,NULL);

		//TODO: Get motion from proxy
		cmd = proxy->get_motion();
		if (cmd!=NULL) {
			//printf("GOT COMMAND\n");
			gonz_set_motion_request(
					(cmd)->angle,
					(cmd)->translation,
					(cmd)->rotation
					);				
			//printf("MM CURCMD %f\t%f\t%f\n",gonz_state.currentMotionGoal.x,gonz_state.currentMotionGoal.y,gonz_state.currentMotionGoal.rotation);

			gonz_main();
		} else {
			//printf("Command Timeout!\n");
			gonz_idle();
		}
		break;

		/* cout<<"EposGonzales::main logging data"<<endl; */
		/* logData(); */

		gettimeofday(&time_cur,NULL);
		//printf("Sleeping for: %ldus\n",current_settings.controllerLoopTime*1000l-TIMEDIFFMS(time_cur,time_last));
		usleep(max(10l,(current_settings.controllerLoopTime-TIMEDIFFMS(time_cur,time_last))*1000l));
	}

	return 0;
}

