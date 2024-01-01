#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <sys/fcntl.h>
#define BUFFER_SIZE 8192
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#include <chrono>
#include <cstring>
#include <format>
#include <future>
#include <sstream>
#include <utility>

#include <tendril/configuration.h>
#include <tendril/network/listener/information.h>
#include <tendril/metrics/server.h>
void tendril::metrics::server::start(tendril::Configuration& configuration) {
}

static int tendril::metrics::server::listen(tendril::network::listener::Information& listener_information) {
	std::cout << "trying to start metrics server\n";
	struct sockaddr_in a;
	int server_socket;
	int yes;
	if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		//perror("socket");
        return -1;
    }
    yes = 1;
    if(setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        //perror("setsockopt");
        close(server_socket);
        return -1;
    }
    memset(&a, 0, sizeof(a));
    a.sin_port = htons(listener_information.address_set.port);
    a.sin_family = AF_INET;
    if(bind(server_socket, (struct sockaddr *) &a, sizeof(a)) == -1) {
        //perror("bind");
        close(server_socket);
        return -1;
    }


    if (server_socket == -1) {
		exit(EXIT_FAILURE);
	}
	for (;;) {
  		struct sockaddr_in client_address;
  		socklen_t address_length = sizeof(client_address);
		memset(&client_address, 0, address_length);
		int connection = accept(server_socket, (struct sockaddr*) &client_address, &address_length);
		// Set nonblocking mode on the socket.
		int flags = fcntl(connection, F_GETFL, 0);
		if (flags == -1) {
			//perror_die("fcntl F_GETFL");
		}
		if (fcntl(connection, F_SETFL, flags | O_NONBLOCK) == -1) {
			//perror_die("fcntl F_SETFL O_NONBLOCK");
		}
		if(connection == -1) {
			//perror_die("accept()");
		} else {
			//reply to metrics request here
		}
    }
    return server_socket;
}

void* tendril::metrics::server::start(void* arg) {
	std::cout << "starting tendril::metrics::server::start\n";
	auto configuration = *(tendril::Configuration*)arg;
	for(;;) {
		
	}
	//listen(configuration.tendril.network.listener.listeners_information.at(0));
	std::cout << "exiting tendril::metrics::server::start\n";
	return 0;
}