#include "config.h"
#include <iostream>
#include <tendril.h>
#include <tendril/network/server.h>
#include <tendril/system.h>
//https://www.jeremyong.com/cpp/2021/01/04/cpp20-coroutines-a-minimal-async-framework/
namespace tendril {
	bool keep_running = false;
}
void tendril::start(int argc, char *argv[]){
	tendril::network::server::serve(8500, 10);
}
void tendril::stop() {

}
void tendril::version() {
	std::cout << "tendril:     " << VERSION << "\n";
	std::cout << "max threads: " << tendril::system::max_threads << "\n";
}