#include "config.h"
#include <iostream>
#include <tendril.h>
#include <tendril/network/server.h>
#include <tendril/queue/manager.h>
#include <tendril/system.h>
namespace tendril {
	bool keep_running = false;
}
void tendril::start(int argc, char *argv[]) {
	if(tendril::queue::manager::initialize("localhost")) {
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