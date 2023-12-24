#include "config.h"
#include <cstdlib>
#include <iostream>
#include <tendril.h>
#include <tendril/network/server.h>
#include <tendril/queue/manager.h>
#include <tendril/system.h>
namespace tendril {
	bool keep_running = false;
}
void tendril::start(int argc, char *argv[]) {
	const char* brokers_list = std::getenv("KAFKA_BROKERS");
	if(!brokers_list) {
		std::cerr << "KAFKA_BROKERS environmental variable must be set" << std::endl;
		exit(1);
	}
	puts(brokers_list);
	if(tendril::queue::manager::initialize(std::string(brokers_list))) {
		tendril::network::server::serve(8500, 10);
	}
	else {
		std::cerr << "Error initializing kafka queue\n";
	}
}
void tendril::stop() {

}
void tendril::version() {
	std::cout << "tendril:     " << VERSION << "\n";
	std::cout << "max threads: " << tendril::system::max_threads << "\n";
}