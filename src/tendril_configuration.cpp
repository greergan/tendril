#include <tendril/configuration.h>

#include <iostream>
void tendril::Configuration::Tendril::Network::Listener::add(tendril::network::listener::Information listener_information) {
	bool listener_found = false;
	for(auto current_listener_information : listeners_information) {
		if(current_listener_information.address_set.address == listener_information.address_set.address
			&& current_listener_information.address_set.port == listener_information.address_set.port) {
			if(listener_information.back_pressure) {
				current_listener_information.back_pressure = listener_information.back_pressure;
			}
			if(listener_information.read_time_out >= 0) {
				current_listener_information.read_time_out = listener_information.read_time_out;
			}
			listener_found = true;
		}
	}
	if(!listener_found) {
		listeners_information.push_back(listener_information);
	}
}