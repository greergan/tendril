#ifndef __TENDRIL__NETWORK__SERVER__H
#define __TENDRIL__NETWORK__SERVER__H
#include <netinet/in.h>
namespace tendril::network::server {
	struct SocketInformation {
		int socket_handle;
		struct sockaddr_in client_address;
	};
	static int listener(int listening_port, int back_pressure);
	static void* run_thread(void* arg);
	int serve(int listening_port, int back_pressure);
};
#endif