#ifndef __TENDRIL__QUEUE__MANAGER__H
#define __TENDRIL__QUEUE__MANAGER__H
#include <tendril/configuration.h>
#include <tendril/queue.h>
namespace tendril::queue::manager {
	bool initialize(tendril::Configuration& configuration);
	tendril::queue::QueuePacket get_some(std::string conversation_id);
	bool send_some(tendril::queue::QueuePacket);
}
#endif