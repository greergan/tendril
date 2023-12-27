#include <iostream>
#include <string>
#include <unordered_map>
#include <librdkafka/rdkafkacpp.h>
#include <tendril/configuration.h>
#include <tendril/queue/kafka.h>
namespace tendril::queue::kafka {
	std::string errstr;
	RdKafka::Conf* configuration;
	RdKafka::KafkaConsumer* consumer;
	RdKafka::Producer* producer;
	std::unordered_map<std::string, tendril::queue::QueuePacket>* reply_queue;
};
void tendril::queue::kafka::DeliveryReportCb::dr_cb(RdKafka::Message &message) {
	std::cerr << "message here\n";
	if(message.err()) {
		std::cerr << "Message delivery failed: " << message.errstr() << std::endl;				
	}
	else {
	std::cerr << "Message delivered to topic " << message.topic_name()
				<< " [" << message.partition() << "] at offset " << message.offset() << std::endl;
	}
}
bool tendril::queue::kafka::initialize(tendril::Configuration& tendril_configuration,
					std::unordered_map<std::string, tendril::queue::QueuePacket>* replies) {
	//rkt - the topic to produce to, previously created with rd_kafka_topic_new()
	reply_queue = replies;
	configuration = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
	DeliveryReportCb message_cb;
	if(configuration->set("bootstrap.servers", tendril_configuration.kafka.bootstrap_servers, errstr) != RdKafka::Conf::CONF_OK) {
		std::cerr << errstr << "\n";
		return false;
	}
	if(configuration->set("dr_cb", &message_cb, errstr) != RdKafka::Conf::CONF_OK) {
		std::cerr << errstr << "\n";
		return false;
	}
	producer = RdKafka::Producer::create(configuration, errstr);
	if(!errstr.empty()) {
		std::cerr << errstr << "\n";
		return false;
	}
	// need to configure group.id
/* 	consumer = RdKafka::KafkaConsumer::create(configuration, errstr);
	if(!errstr.empty()) {
		std::cerr << errstr << "\n";
		return false;
	} */
	return true;
}
//RdKafka::Producer::produce(std::string, int32_t, int, void*, size_t, const void*, size_t, int64_t, RdKafka::Headers*, void*)
RdKafka::ErrorCode tendril::queue::kafka::produce(tendril::queue::QueuePacket packet) {
	std::string raw_tcp_messages_topic = "raw_tcp_messages";
	auto error_code = producer->produce(raw_tcp_messages_topic, RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY,
        				const_cast<char *>(packet.data.c_str()), packet.data.length(),
						const_cast<char *>(packet.conversation_id.c_str()), packet.conversation_id.length(),
						USE_CURRENT_TIME_STAMP ,NULL, NULL);
	//RdKafka::err2str(error_code);
	return error_code;
}
