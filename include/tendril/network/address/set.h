#ifndef __TENDRIL__NETWORK__ADDRESS__SET__H
#define __TENDRIL__NETWORK__ADDRESS__SET__H
#include <string>
namespace tendril::network::address {
	struct AddressSet {
		int port;
		std::string address;
		bool empty(void);
	};
	AddressSet string_to_address_set(char* address_string);
	AddressSet string_to_address_set(std::string& address_string);
}
#endif