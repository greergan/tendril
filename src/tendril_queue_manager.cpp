#include <tendril/queue/manager.h>
bool tendril::queue::manager::send_some(tendril::queue::QueuePacket) {
	return true;
}
tendril::queue::QueuePacket tendril::queue::manager::get_some(std::string conversation_id) {
	tendril::queue::QueuePacket reply;
	reply.data = "HTTP/1.1 200 OK\r\nContent-Length:15\r\nContent-Type: text/html\r\n\r\n<html></html>\r\n";
	reply.close_socket = true;
	return reply;
}