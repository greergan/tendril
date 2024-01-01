#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <functional>
#include <future>
#include <tendril/client/connection/information.h>
#include <tendril/network/listener.h>
#include <tendril/network/listener/information.h>

#include <iostream>
void tendril::network::listener::standard(
		tendril::network::listener::Information& listener_information,
		std::function<void(tendril::client::connection::Information&)> client_handler) {
	std::cout << "starting tendril::network::listener::standard\n";
	struct sockaddr_in listener_socket_address;
	int server_socket;
	int socket_options = 1;
	if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
        exit(1);
    }
    if(setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &socket_options, sizeof(socket_options)) == -1) {
        perror("setsockopt");
        close(server_socket);
        exit(1);
    }
    memset(&listener_socket_address, 0, sizeof(listener_socket_address));
	std::cout << "binding to address " << listener_information.address_set.address << " port " << listener_information.address_set.port << std::endl;
	listener_socket_address.sin_addr.s_addr = inet_addr(listener_information.address_set.address.c_str());
    listener_socket_address.sin_port = htons(listener_information.address_set.port);
    listener_socket_address.sin_family = AF_INET;
    if(bind(server_socket, (struct sockaddr *) &listener_socket_address, sizeof(listener_socket_address)) == -1) {
        perror("bind");
        close(server_socket);
        exit(1);
    }
    //printf("tendril::network::server::listener:: accepting connections on port %d\n", listening_port);
    auto result = listen(server_socket, listener_information.back_pressure);
	if(result == -1) {
		perror("listen");
		exit(1);
	}
	for (;;) {
  		struct sockaddr_in client_address;
  		socklen_t address_length = sizeof(client_address);
		memset(&client_address, 0, address_length);
		int client_connection = accept(server_socket, (struct sockaddr*) &client_address, &address_length);
		if(client_connection == -1) {
			perror("accept");
			exit(1);
		}
		// Set nonblocking mode on the socket.
		int flags = fcntl(client_connection, F_GETFL, 0);
		if (flags == -1) {
			perror("fcntl");
			exit(1);
		}
		if (fcntl(client_connection, F_SETFL, flags | O_NONBLOCK) == -1) {
			perror("fcntl");
			exit(1);
		}
		tendril::client::connection::Information client_information;
		client_information.read_timeout = listener_information.read_time_out;
		client_information.client_address = client_address;
		client_information.socket_handle = client_connection;
		std::async(std::ref(client_handler), std::ref(client_information));
    }

	std::cout << "ending tendril::network::listener::standard\n";
	return;
}