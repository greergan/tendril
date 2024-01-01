#ifndef __TENDRIL__NETWORK__SERVER__H
#define __TENDRIL__NETWORK__SERVER__H
#include <netinet/in.h>
#include <tendril/configuration.h>
#include <tendril/network/listener/information.h>
namespace tendril::network::server {
	struct SocketInformation {
		int socket_handle;
		struct sockaddr_in client_address;
	};
};
#endif