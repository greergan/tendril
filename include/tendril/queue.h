#ifndef __TENDRIL__QUEUE__H
#define __TENDRIL__QUEUE__H
#include <string>
namespace tendril::queue {
	struct QueuePacket {
		std::string data;
		std::string conversation_id;
		bool close_socket = false;
		bool data_is_oob = false;
	};
};
#endif