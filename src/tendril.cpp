#include "config.h"
#include <future>
#include <iostream>
#include <thread>
#include <tendril.h>
#include <tendril/client/connection/handler/metrics.h>
#include <tendril/configuration/handler.h>
#include <tendril/metrics>
#include <tendril/network/listener.h>
#include <tendril/network/server.h>
#include <tendril/queue/manager.h>
namespace tendril {
	bool keep_running = false;
}
void tendril::start(int argc, char *argv[]) {
	bool configured_required;
	auto configuration = tendril::configuration::handler::initialize(configured_required);

	std::cout << "serve " << configuration.tendril.network.metrics.listener.serve << std::endl;
	std::cout << "port " << configuration.tendril.network.metrics.listener.information.address_set.port << std::endl;
	std::cout << "address " << configuration.tendril.network.metrics.listener.information.address_set.address << std::endl;
	std::cout << "number of listeners: " << configuration.tendril.network.listener.listeners_information.size() << std::endl;
	for(auto listener_information : configuration.tendril.network.listener.listeners_information) {
		std::cout << "port " << listener_information.address_set.port << std::endl;
		std::cout << "address " << listener_information.address_set.address << std::endl;
		std::cout << "back_pressure " << listener_information.back_pressure << std::endl;
		std::cout << "read_time_out " << listener_information.read_time_out << std::endl;
	}
	std::cout << "kafka bootstrap servers " << configuration.kafka.bootstrap_servers << std::endl;

	auto cb = [](){
		std::cout << "in callback\n";
		while(true);
	};
	if(tendril::queue::manager::initialize(configuration)) {
		std::vector<std::thread> listener_threads;
/* 		for(unsigned int i = 0; i < configuration.tendril.network.listener.listeners_information.size(); ++i) {
			configuration.tendril.network.listener.listeners_information.at(i).client_handler = cb;
			listener_threads.push_back(std::thread(tendril::network::listener::standard, std::ref(
				configuration.tendril.network.listener.listeners_information.at(i)
			)));
		} */
		listener_threads.push_back(
			std::thread(tendril::network::listener::standard,
				std::ref(configuration.tendril.network.metrics.listener.information),
				std::ref(tendril::client::connection::handler::metrics::handle_client_connection)));
		for(unsigned int i = 0; i < listener_threads.size(); ++i) {
			listener_threads.at(i).join();
		}
		//while(true);
	}
	else {
		std::cerr << "Error initializing kafka queue\n";
	}
}
void tendril::stop() {

}
void tendril::version() {
	std::cout << "tendril:     " << VERSION << "\n";
}