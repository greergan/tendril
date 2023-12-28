/* #include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <unistd.h> */

#include <fstream>
#include <iostream>

#include <tendril/system/information.h>

/* struct utsname system_uts_information;
uname(&system_uts_information);
 */
namespace tendril::system::information {
/* 	sysinfo linux_system_information;
	if(!sysinfo(&linux_system_information)) {
		//throw
	} */
}

long tendril::system::get_system_max_threads(void) {
	std::string string_value;
	std::ifstream max_threads_stream;
	max_threads_stream.open("/proc/sys/kernel/threads-max");
	if(max_threads_stream.is_open()) {
		getline(max_threads_stream, string_value);
		max_threads_stream.close();
	}
	else {

	}
	return(std::stol(string_value));
}
