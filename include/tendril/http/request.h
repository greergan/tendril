#ifndef __TENDRIL__HTTP__REQUEST__H
#define __TENDRIL__HTTP__REQUEST__H
#include <tendril/http/headers.h>
namespace tendril::http {
	struct Request {
		Request(void);
		Request(char* request_pointer);
		Request(std::string& request_string);
		tendril::http::Headers& headers(void);
		void path(std::string value);
		void path(std::string* value);
		std::string& path(void);
		void method(std::string value);
		void method(std::string* value);
		std::string& method(void);
		void version(std::string value);
		void version(std::string* value);
		std::string& version(void);
		private:
			std::string method_string;
			std::string path_string;
			std::string version_string;
			Headers headers_map;
	};
};
#endif