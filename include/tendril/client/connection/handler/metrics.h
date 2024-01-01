#ifndef __TENDRIL__CLIENT__CONNECTION__HANDLER__METRICS__H
#define __TENDRIL__CLIENT__CONNECTION__HANDLER__METRICS__H
#include <tendril/client/connection/information.h>
#include <tendril/http/headers.h>
namespace tendril::client::connection::handler::metrics {
	static std::string get_metrics(void);
	static std::string handle_request(std::string request_string);
	void handle_client_connection(tendril::client::connection::Information& client_connection_information);
}
#endif