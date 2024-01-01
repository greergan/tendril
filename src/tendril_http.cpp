#include <algorithm>
#include <string>
#include <unordered_map>
#include <tendril/http/headers.h>
#include <tendril/http/parser.h>
#include <tendril/http/response.h>
#include <tendril/http/request.h>

#include <iostream>


/* tendril::http::Headers */
std::unordered_map<std::string, std::string>& tendril::http::Headers::get(void) {
	return headers;
}
void tendril::http::Headers::set(std::string key, std::string value) {
	headers[key] = value;
}
tendril::http::Headers& tendril::http::Response::headers(void) {
	return headers_map;
}
/* tendril::http::Response */
void tendril::http::Response::version(std::string value) {
	version_string = value;
}
void tendril::http::Response::version(std::string* value) {
	version_string = std::string(*value);
}
std::string& tendril::http::Response::version(void) {
	return version_string;
}
void tendril::http::Response::body(std::string value) {
	body_string = value;
}
void tendril::http::Response::body(std::string* value) {
	body_string = std::string(*value);
}
std::string& tendril::http::Response::body(void) {
	return body_string;
}
void tendril::http::Response::response_code(int value) {
	response_code_int = value;
	switch(response_code_int) {
		case 200: response_code_string_value = "OK"; break;
		case 404: response_code_string_value = "Not Found"; break;
		case 501: response_code_string_value = "Not Implemented"; break;
		case 505: response_code_string_value = "HTTP Version Not Supported"; break;
	}
}
int tendril::http::Response::response_code(void) {
	return response_code_int;
}
std::string& tendril::http::Response::response_code_string(void) {
	return response_code_string_value;
}
/* tendril::http::Request */
tendril::http::Request::Request(void) {}
tendril::http::Request::Request(char* request_pointer) {
	tendril::http::parser::parse_http_request(request_pointer, this);
}
tendril::http::Request::Request(std::string& request_string) {
	tendril::http::parser::parse_http_request(request_string, this);
}
tendril::http::Headers& tendril::http::Request::headers(void) {
	return headers_map;
}
void tendril::http::Request::method(std::string value) {
	method_string = value;
}
void tendril::http::Request::method(std::string* value) {
	method_string = std::string(*value);
}
std::string& tendril::http::Request::method(void) {
	return method_string;
}
void tendril::http::Request::path(std::string value) {
	path_string = value;
}
void tendril::http::Request::path(std::string* value) {
	path_string = std::string(*value);
}
std::string& tendril::http::Request::path(void) {
	return path_string;
}
void tendril::http::Request::version(std::string value) {
	version_string = value;
}
void tendril::http::Request::version(std::string* value) {
	version_string = std::string(*value);
}
std::string& tendril::http::Request::version(void) {
	return version_string;
}