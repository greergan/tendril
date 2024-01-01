#ifndef __TENDRIL__CLIENT__CONNECTION__INFORMATION__H
#define __TENDRIL__CLIENT__CONNECTION__INFORMATION__H
#include <netinet/in.h>
namespace tendril::client::connection {
	struct Information {
		int read_timeout;
		int socket_handle;
		struct sockaddr_in client_address;
	};
}
#endif