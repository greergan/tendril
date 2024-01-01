#ifndef __TENDRIL__CLIENT__CONNECTION__HANDLER__METRICS__H
#define __TENDRIL__CLIENT__CONNECTION__HANDLER__METRICS__H
#include <tendril/client/connection/information.h>
#include <tendril/http/headers.h>
#include <tendril/metrics.h>
namespace tendril::client::connection::handler::metrics {
	static std::string get_metrics(tendril::Metrics& metrics);
	static std::string handle_request(char* data, tendril::Metrics& metrics);
	void handle_client_connection(tendril::client::connection::Information& client_connection_information, tendril::Metrics& metrics);
}
#endif