#include <chrono>
#include <iostream>
#include <unordered_map>
#include <tendril/queue/kafka.h>
#include <tendril/queue/manager.h>
#include <librdkafka/rdkafkacpp.h>
namespace tendril::queue::manager {
	std::unordered_map<std::string, tendril::queue::QueuePacket> reply_queue;
}
bool tendril::queue::manager::initialize(tendril::Configuration& configuration) {
	return tendril::queue::kafka::initialize(configuration, &reply_queue);
}
tendril::queue::QueuePacket tendril::queue::manager::get_some(std::string conversation_id) {
	tendril::queue::QueuePacket reply_packet;
	using namespace std::chrono_literals;
	auto loop_start_time = std::chrono::steady_clock::now();
	for(;;) {
		if(auto packet_tuple = reply_queue.find(conversation_id); packet_tuple != reply_queue.end()) {
			reply_packet = std::move(packet_tuple->second);
			reply_queue.erase(conversation_id);
			return reply_packet;
		}
		if(std::chrono::steady_clock::now() > loop_start_time + 4s) {
			break;
		}
	}
	reply_packet.close_socket = true;
	return reply_packet;
}
bool tendril::queue::manager::send_some(tendril::queue::QueuePacket packet) {
	//https://github.com/confluentinc/librdkafka/blob/master/examples/rdkafka_example.cpp#L510
	auto error_code = tendril::queue::kafka::produce(packet);
	if(error_code) {
		//std::cerr << "tendril::queue::manager::send_some::error_code: " << RdKafka::err2str(error_code) << std::endl;
		return false;
	}
	return true;
}
