#ifndef __TENDRIL__METRICS__H
#define __TENDRIL__METRICS__H
#include <string>
#include <unordered_map>
#include <tendril/metrics/counter.h>
namespace tendril {
	struct Metrics {
		std::string pid_string;
		std::unordered_map<std::string, tendril::metrics::Counter> counters;
		void add_counter(std::string key, std::string help, std::string type, std::string format);
		Metrics(void);
	};
};
#endif
