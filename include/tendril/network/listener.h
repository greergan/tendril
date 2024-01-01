#ifndef __TENDRIL__NETWORK__LISTENER__H
#define __TENDRIL__NETWORK__LISTENER__H
#include <functional>
#include <tendril/metrics.h>
#include <tendril/network/listener/information.h>
namespace tendril::network::listener {
	void standard(
		tendril::network::listener::Information& listener_information,
		std::function<void(tendril::client::connection::Information&, tendril::Metrics&)> client_handler,
		tendril::Metrics& metrics);
};
#endif