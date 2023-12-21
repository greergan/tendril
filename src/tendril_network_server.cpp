#include <string>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/fcntl.h>
#define perror_die(str) do { \
   fprintf(stderr,"%s/%s(): \n", \
           __FILE__ ,__func__ );\
           perror(str); exit(1); \
		   } while(0);
int setNonblocking(int fd)
{
    int flags;

    // If they have O_NONBLOCK, use the Posix way to do it
#if defined(O_NONBLOCK)
    // Fixme: O_NONBLOCK is defined but broken on SunOS 4.1.x and AIX 3.2.5.
    if (-1 == (flags = fcntl(fd, F_GETFL, 0)))
        flags = 0;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
#else
    // Otherwise, use the old way of doing it
    flags = 1;
    return ioctl(fd, FIONBIO, &flags);
#endif
}

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
#include <tendril/network/server.h>
#include <tendril/queue.h>
#include <tendril/queue/manager.h>
static int tendril::network::server::listener(int listening_port, int back_pressure) {
	struct sockaddr_in a;
	int server_socket;
	int yes;
	if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
        return -1;
    }
    yes = 1;
    if(setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        perror("setsockopt");
        close(server_socket);
        return -1;
    }
    memset(&a, 0, sizeof(a));
    a.sin_port = htons(listening_port);
    a.sin_family = AF_INET;
    if(bind(server_socket, (struct sockaddr *) &a, sizeof(a)) == -1) {
        perror("bind");
        close(server_socket);
        return -1;
    }
    printf("tendril::network::server::listener:: accepting connections on port %d\n", listening_port);
    listen(server_socket, back_pressure);
    return server_socket;
}
void* tendril::network::server::run_thread(void* arg) {
	int bytes_read = 0, bytes_written = 0, nfds = 0;
	fd_set read_set, write_set, except_set;
	char read_buffer[BUFFER_SIZE];
	auto socket_information = *(tendril::network::server::SocketInformation*)arg;
	std::stringstream conversation_id;
	conversation_id << ntohs(socket_information.client_address.sin_port);
	conversation_id << ":" << inet_ntoa(socket_information.client_address.sin_addr);
	conversation_id << ":" << std::chrono::high_resolution_clock::now().time_since_epoch();
	printf("tendril::network::server::run_thread:: handling socket %d\n", socket_information.socket_handle);
	for(;;) {
		FD_ZERO(&read_set);
		FD_ZERO(&write_set);
		FD_ZERO(&except_set);
		FD_SET(socket_information.socket_handle, &read_set);
		tendril::queue::QueuePacket new_queue_packet;
		new_queue_packet.conversation_id = conversation_id.str();
		printf("tendril::network::server::run_thread::read waiting for select\n");
		int selected = select(socket_information.socket_handle + 1, &read_set, NULL, &except_set, NULL);
		if(selected == -1 && errno == EINTR) {
			continue;
		}
		if(selected == -1) {
			break;
		}
		if(FD_ISSET(socket_information.socket_handle, &read_set)) {
			memset(read_buffer, '\0', sizeof(read_buffer));
			bytes_read = read(socket_information.socket_handle, read_buffer, BUFFER_SIZE);
			printf("tendril::network::server::run_thread:: bytes_read %d\n", bytes_read);
			if(bytes_read < 1) {
				break;
			}
			else {
				if(read_buffer) {
					new_queue_packet.data = std::string(read_buffer);
					auto result = std::async(tendril::queue::manager::send_some, new_queue_packet);
					bool received = result.get();
					printf("tendril::network::server::run_thread::send_some() received %d\n", received);
					if(received) {
						break;
					}
				}
			}
		}
		if(FD_ISSET(socket_information.socket_handle, &except_set)) {
			char c;
			bytes_read += recv(socket_information.socket_handle, &c, 1, MSG_OOB);
			printf("tendril::network::server::run_thread:: bytes_read %d MSG_OOB\n", bytes_read);
			if(bytes_read < 1) {
				break;
			}
			else {
				memset(read_buffer, '\0', sizeof(read_buffer));
				read_buffer[0] = c;
			}   
		}
	}
	for(;;) {
		FD_ZERO(&write_set);
		FD_ZERO(&except_set);
		FD_SET(socket_information.socket_handle, &write_set);
		auto reply = std::async(tendril::queue::manager::get_some, conversation_id.str());
		auto reply_packet = reply.get();
		printf("tendril::network::server::run_thread::write waiting for select\n");
		int selected = select(socket_information.socket_handle + 1, NULL, &write_set, NULL, NULL);
		if(selected == -1 && errno == EINTR) {
			continue;
		}
		if(selected == -1) {
			break;
		}
		if(FD_ISSET(socket_information.socket_handle, &write_set)) {
			printf("tendril::network::server::run_thread:: writing bytes\n");
			bytes_written = send(socket_information.socket_handle, reply_packet.data.c_str(), reply_packet.data.length(), 0);
			printf("tendril::network::server::run_thread:: bytes_written %d\n", bytes_written);
			if(reply_packet.close_socket) {
				break;
			}
		}
	}	
	printf("tendril::network::server::run_thread:: closing socket %d\n", socket_information.socket_handle);
	shutdown(socket_information.socket_handle, SHUT_WR);
	close(socket_information.socket_handle);
  	return 0;
}
int tendril::network::server::serve(int listening_port, int back_pressure) {
	int server_socket;
	signal(SIGPIPE, SIG_IGN);
	server_socket = listener(listening_port, back_pressure);
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
			perror_die("fcntl F_GETFL");
		}
		if (fcntl(connection, F_SETFL, flags | O_NONBLOCK) == -1) {
			perror_die("fcntl F_SETFL O_NONBLOCK");
		}
		if(connection == -1) {
			perror_die("accept()");
		} else {
  			pthread_t the_thread;
			SocketInformation socket_information;
  			socket_information.socket_handle = connection;
			socket_information.client_address = client_address;
  			pthread_create(&the_thread, NULL, run_thread, &socket_information);
  			pthread_detach(the_thread);
		}
    }
    exit(EXIT_SUCCESS);
}