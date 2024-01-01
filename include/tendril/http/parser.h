#ifndef __TENDRIL__HTTP__PARSER__H
#define __TENDRIL__HTTP__PARSER__H
#include <string>
#include <tendril/http/request.h>
namespace tendril::http::parser {
	static void parse_line_1(std::string& method_string, tendril::http::Request* request);
	void parse_http_request(const char* request_pointer, tendril::http::Request* request);
	void parse_http_request(std::string& request_string, tendril::http::Request* request);
}
#endif