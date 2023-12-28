#ifndef __TENDRIL__CONFIGURATION__H
#define __TENDRIL__CONFIGURATION__H
#include <vector>
#include <string>
#include <tendril/network/address/set.h>
#include <tendril/network/listener/information.h>
namespace tendril {
	struct Configuration {
		struct Tendril {
			struct Network {
				struct Listener {
					std::vector<tendril::network::listener::Information> listeners_information;
					void add(tendril::network::listener::Information);
				} listener;
				struct Metrics {
					struct Listener {
						bool serve;
						tendril::network::listener::Information information;
					} listener;
				} metrics;
			} network;
		} tendril;
		struct Kafak {
			std::string bootstrap_servers;
		} kafka;
		struct System {
			//number of threads = total virtual memory / (stack size*1024*1024)
			long max_threads;
			std::string os_version;
			struct Process {
				
			} process;
		} system;
	};
};
#endif
