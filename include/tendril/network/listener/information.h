#ifndef __TENDRIL__NETWORK__LISTENER__INFORMATION__H
#define __TENDRIL__NETWORK__LISTENER__INFORMATION__H
#include <functional>
#include <tendril/network/address/set.h>
namespace tendril::network::listener {
	struct Information {
		tendril::network::address::AddressSet address_set;
		int back_pressure;
		int read_time_out;
	};
}
#endif