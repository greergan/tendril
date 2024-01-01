#ifndef __TENDRIL__NETWORK__LISTENER__H
#define __TENDRIL__NETWORK__LISTENER__H
#include <functional>
#include <tendril/network/listener/information.h>
namespace tendril::network::listener {
	void standard(tendril::network::listener::Information& listener_information,
			std::function<void(tendril::client::connection::Information&)> client_handler);
};
#endif