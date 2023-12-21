#ifndef __TENDRIL__QUEUE__MANAGER__H
#define __TENDRIL__QUEUE__MANAGER__H
#include <tendril/queue.h>
namespace tendril::queue::manager {
	bool send_some(tendril::queue::QueuePacket);
	tendril::queue::QueuePacket get_some(std::string conversation_id);
}
#endif