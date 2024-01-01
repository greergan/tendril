#ifndef __TENDRIL__QUEUE__KAFKA__H
#define __TENDRIL__QUEUE__KAFKA__H
#include <string>
#include <unordered_map>
#include <tendril/configuration.h>
#include <tendril/queue.h>
#include <librdkafka/rdkafkacpp.h>
#define USE_CURRENT_TIME_STAMP 0
namespace tendril::queue::kafka {
	class DeliveryReportCb : public RdKafka::DeliveryReportCb {
		public:
			void dr_cb(RdKafka::Message& message);
	};
	bool initialize(tendril::Configuration& tendril_configuration, std::unordered_map<std::string, tendril::queue::QueuePacket>* replies);
	RdKafka::ErrorCode produce(tendril::queue::QueuePacket packet);
};
#endif