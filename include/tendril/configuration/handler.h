#ifndef __TENDRIL__CONFIGURATION__HANDLER__H
#define __TENDRIL__CONFIGURATION__HANDLER__H
#include <tendril/configuration.h>
namespace tendril::configuration::handler {
	static void handle_environmental_variables(void);
	static void handle_environmental_variables_kafka(void);
	static void handle_environmental_variables_metrics(void);
	static void handle_initialization_file(void);
	tendril::Configuration& initialize(bool& configured_required);
};
#endif