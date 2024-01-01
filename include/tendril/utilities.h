#ifndef __TENDRIL__UTILITIES__H
#define __TENDRIL__UTILITIES__H
#include <string>
namespace tendril::utilities {
	bool get_bool_value(char* value);
	int get_int_value(char* value);
	int get_int_value(std::string value);
	int get_int_value(std::string* value);
}
#endif