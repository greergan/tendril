#include <sstream>
#include <string>
#include <vector>
#include <tendril/configuration/handler.h>
#include <tendril/network/address/set.h>
#include <tendril/system/information.h>
#include <tendril/system/process/information.h>
#include <tendril/utilities.h>
namespace tendril::configuration::handler {
	tendril::Configuration configuration;
	bool required_configured = false;
};
void tendril::configuration::handler::handle_environmental_variables(void) {
	handle_environmental_variables_kafka();
	handle_environmental_variables_metrics();
	if(std::getenv("TENDRIL_NETWORK_LISTENERS")) {
		std::vector<int> back_pressure_vector;
		std::vector<int> read_time_out_vector;
		if(std::getenv("TENDRIL_NETWORK_LISTENERS_BACK_PRESSURE")) {
			auto back_pressure_string = std::string(std::getenv("TENDRIL_NETWORK_LISTENERS_BACK_PRESSURE"));
			std::stringstream back_pressure_list_stream{back_pressure_string};
			std::string back_pressure_string_value;
			while(getline(back_pressure_list_stream, back_pressure_string_value, ',')) {
				auto back_pressure_int_value = tendril::utilities::get_int_value(back_pressure_string_value);
				if(back_pressure_int_value) {
					back_pressure_vector.push_back(back_pressure_int_value);
				}
			}
		}
		if(std::getenv("TENDRIL_NETWORK_LISTENERS_READ_TIMEOUT")) {
			auto read_time_out_string = std::string(std::getenv("TENDRIL_NETWORK_LISTENERS_READ_TIMEOUT"));
			std::stringstream read_time_out_list_stream{read_time_out_string};
			std::string read_time_out_string_value;
			while(getline(read_time_out_list_stream, read_time_out_string_value, ',')) {
				auto read_time_out_int_value = tendril::utilities::get_int_value(read_time_out_string_value);
				if(read_time_out_int_value) {
					read_time_out_vector.push_back(read_time_out_int_value);
				}
			}
		}
		if(!back_pressure_vector.size()) {
			back_pressure_vector.push_back(100);
		}
		if(!read_time_out_vector.size()) {
			read_time_out_vector.push_back(500);
		}
		auto address_list = std::string(std::getenv("TENDRIL_NETWORK_LISTENERS"));
		std::stringstream address_list_stream{address_list};
		std::string address;
		int count = 0;
    	while(getline(address_list_stream, address, ',')) {
			auto address_set = tendril::network::address::string_to_address_set(address);
			tendril::network::listener::Information listener_information;
			listener_information.address_set = address_set;
			if(back_pressure_vector.size() >= count) {
				listener_information.back_pressure = back_pressure_vector.at(count);
			}
			if(read_time_out_vector.size() >= count) {
				listener_information.read_time_out = read_time_out_vector.at(count);
			}
			configuration.tendril.network.listener.add(listener_information);
		}
    }
}
void tendril::configuration::handler::handle_environmental_variables_kafka(void) {
	if(std::getenv("TENDRIL_KAFKA_BOOTSTRAP_SERVERS")) {
		configuration.kafka.bootstrap_servers = std::string(std::getenv("TENDRIL_KAFKA_BOOTSTRAP_SERVERS"));
	}
}
void tendril::configuration::handler::handle_environmental_variables_metrics(void) {
	tendril::network::address::AddressSet address_set;
	if(std::getenv("TENDRIL_METRICS_SERVER_ADDRESS")) {
		address_set = tendril::network::address::string_to_address_set(std::getenv("TENDRIL_METRICS_SERVER_ADDRESS"));
		configuration.tendril.network.metrics.listener.information.address_set = address_set;
	}
	if(address_set.address.empty()) {
		configuration.tendril.network.metrics.listener.information.address_set.address = "127.0.0.1";
	}
	if(!address_set.port) {
		configuration.tendril.network.metrics.listener.information.address_set.port = 9090;
	}
	if(std::getenv("TENDRIL_METRICS_SERVER_SERVE")) {
		configuration.tendril.network.metrics.listener.serve
			= tendril::utilities::get_bool_value(std::getenv("TENDRIL_METRICS_SERVER_SERVE"));
	}
	else {
		configuration.tendril.network.metrics.listener.serve = false;
	}
}
void tendril::configuration::handler::handle_initialization_file(void) {

}
tendril::Configuration& tendril::configuration::handler::initialize(bool& configured_required) {
	required_configured = &configured_required;
	configuration.system.max_threads = tendril::system::get_system_max_threads();
	handle_initialization_file(); // first
	handle_environmental_variables(); // overrides file variables
	return configuration;
}