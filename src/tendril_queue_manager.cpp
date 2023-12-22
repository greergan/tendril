#include <tendril/queue/kafka.h>
#include <tendril/queue/manager.h>
#include <librdkafka/rdkafkacpp.h>
bool tendril::queue::manager::initialize(std::string brokers) {
	return tendril::queue::kafka::initialize(brokers);
}
tendril::queue::QueuePacket tendril::queue::manager::get_some(std::string conversation_id) {
	tendril::queue::QueuePacket reply;
	reply.data = "HTTP/1.1 200 OK\r\nContent-Length:20\r\nContent-Type: text/html\r\n\r\n<html>hello</html>\r\n";
	reply.close_socket = true;
	return reply;
}
bool tendril::queue::manager::send_some(tendril::queue::QueuePacket packet) {
	auto error_code = tendril::queue::kafka::produce(packet);
	if(error_code) {
		//std::cerr << "tendril::queue::manager::send_some::error_code: " << error_code << "\n";
		return false;
	}
	return true;
}
