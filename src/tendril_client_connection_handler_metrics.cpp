#include <arpa/inet.h>
#include <errno.h>
#include <future>
#include <netinet/in.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <tendril/client/connection/handler/metrics.h>
#include <tendril/http/response.h>
#include <tendril/http/request.h>
#include <tendril/metrics.h>
#include <tendril/metrics/counter.h>

#include <iostream>
#define BUFFER_SIZE 22
static std::string tendril::client::connection::handler::metrics::get_metrics(tendril::Metrics& metrics) {
	metrics.counters["metrics_requests"].inc();
	std::stringstream metrics_stream;
	std::ifstream filestat("/proc/self/stat");
	std::string line;
	getline(filestat, line);
	if(line.length() > 0) {
		std::stringstream line_stream(line);
		std::string value;
		int count = 1;
		while(getline(line_stream, value, ' ')) {
			if(count == 20) {
				metrics_stream << "# tendril_process_threads_running number of threads running in a specific process" << std::endl;
				metrics_stream << "# tendril_process_threads_running number summary" << std::endl;
				metrics_stream << "tendril_process_threads_running" << metrics.pid_string << " " << value << std::endl;
			}
			count++;
		}
	}
	for(auto& [key, metric] : metrics.counters) {
		metrics_stream << "# " << metric.help << std::endl;
		metrics_stream << "# " << metric.type << std::endl;
		metrics_stream << metric.format << " " << metric.count << std::endl;
	}
	return metrics_stream.str();
}
void tendril::client::connection::handler::metrics::handle_client_connection(
			tendril::client::connection::Information& client_connection_information,
			tendril::Metrics& metrics) {
	metrics.counters["threads_started"].inc();
	std::future<std::string> response;
	timeval timeout;
	double  bytes_read = 0;
	double  bytes_written = 0;
	char read_buffer[BUFFER_SIZE];
	std::string response_string;
	fd_set read_set, write_set, except_set;
	if(client_connection_information.read_timeout > -1) {
		timeout.tv_usec = client_connection_information.read_timeout;
	}
	timeout.tv_usec = 1000;

	for(;;) {
		FD_ZERO(&read_set);
		FD_ZERO(&except_set);
		FD_SET(client_connection_information.socket_handle, &read_set);
		int selected = select(client_connection_information.socket_handle + 1, &read_set, NULL, &except_set, NULL);
		if(selected == -1 && errno == EINTR) {
			continue;
		}
		if(selected == -1) {
			break;
		}
		if(FD_ISSET(client_connection_information.socket_handle, &read_set)) {
			memset(read_buffer, '\0', sizeof(read_buffer));
			bytes_read = read(client_connection_information.socket_handle, read_buffer, BUFFER_SIZE);
			if(*read_buffer) {
				response = std::async(handle_request, read_buffer, std::ref(metrics));
				response_string = response.get();
			}
			break;
		}
		if(FD_ISSET(client_connection_information.socket_handle, &except_set)) {
			char c;
			bytes_read += recv(client_connection_information.socket_handle, &c, 1, MSG_OOB);
			if(bytes_read < 1) {
				break;
			}
			else {
				memset(read_buffer, '\0', sizeof(read_buffer));
				read_buffer[0] = c;
			}   
		}
	}
	std::cout << "waiting to write\n";
	for(;;) {
		FD_ZERO(&write_set);
		FD_ZERO(&except_set);
		FD_SET(client_connection_information.socket_handle, &write_set);
		int selected = select(client_connection_information.socket_handle + 1, NULL, &write_set, NULL, NULL);
		if(selected == -1 && errno == EINTR) {
			continue;
		}
		if(selected == -1) {
			break;
		}
		if(FD_ISSET(client_connection_information.socket_handle, &write_set)) {
			bytes_written = send(client_connection_information.socket_handle, response_string.c_str(), response_string.length(), 0);
			break;
		}
	}
	shutdown(client_connection_information.socket_handle, SHUT_WR);
	close(client_connection_information.socket_handle);
	metrics.counters["threads_ended"].inc();
}
static std::string tendril::client::connection::handler::metrics::handle_request(char* request_pointer, tendril::Metrics& metrics) {
	std::cout << "tendril::client::connection::handler::metrics::handle_request\n";
	tendril::http::Request request(request_pointer);
	tendril::http::Response response;
	if(request.version() == "HTTP/1.1") {
		response.version(request.version());
		if(request.method() == "GET") {
			if(request.path() == "/") {
				response.body("<html><div>Tendril metrics</div><a href=\"/metrics\">metrics</a></html>");
				response.headers().set("Content-type", "text/html");
				response.headers().set("Content-length", std::to_string(response.body().length()));
				response.response_code(200);
			}
			else if(request.path() == "/metrics") {
				auto result = std::async(get_metrics, std::ref(metrics));
				response.body(result.get());
				response.headers().set("Content-type", "text/plain");
				response.headers().set("Content-length", std::to_string(response.body().length() + 1));
				response.response_code(200);
			}
			else {
				response.response_code(404);
			}
		}
		else {
			response.response_code(501);
		}
	}
	else {
		response.version("HTTP/1.1");
		response.response_code(505);
	}
	std::stringstream response_stream;
	response_stream << response.version() << " " << response.response_code() << " " << response.response_code_string() << "\r\n";
	for(auto& [key, value] : response.headers().get()) {
		response_stream << key << ": " << value << "\r\n";
	}
	response_stream << "\r\n\r\n" << response.body() << "\r\n";
	//std::cout << response_stream.str();
	std::cout << "tendril::client::connection::handler::metrics::handle_request done\n";
	return response_stream.str();
}