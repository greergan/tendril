#include <cstdlib>
#include <string>
#include <tendril/network/address/set.h>
#include <tendril/utilities.h>
bool tendril::network::address::AddressSet::empty() {
	return (!port && address.empty()) ? true : false;
}
tendril::network::address::AddressSet tendril::network::address::string_to_address_set(char* address_string) {
	std::string new_string(address_string);
	return string_to_address_set(new_string);
};
tendril::network::address::AddressSet tendril::network::address::string_to_address_set(std::string& address_string) {
	AddressSet address_set;
	if(!address_string.empty()) {
		int delimiter_position = address_string.find(":");
		if(delimiter_position) {
			address_set.address = address_string.substr(0, delimiter_position);
		}
		if(address_string.length() > delimiter_position) {
			auto port = tendril::utilities::get_int_value(address_string.substr(delimiter_position + 1));
			if(port) {
				address_set.port = port;
			}
		}
	}
	return address_set;
}