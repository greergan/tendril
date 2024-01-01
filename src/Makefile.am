#https://stackoverflow.com/questions/70584133/when-using-libadd-in-automake-libtool-links-incorrectly
# might need this for windows linking -> libbar_la_LDFLAGS += -no-undefined
bin_PROGRAMS  = tendril
tendril_SOURCES  = main.cpp \
					tendril.cpp \
					tendril_client_connection_handler_metrics.cpp \
					tendril_configuration.cpp \
					tendril_configuration_handler.cpp \
					tendril_http.cpp \
					tendril_http_parser.cpp \
					tendril_network_address_set.cpp \
					tendril_network_listener.cpp \
					tendril_queue_manager.cpp \
					tendril_queue_kafka.cpp  \
					tendril_utilities.cpp \
					system_information.cpp
tendril_CPPFLAGS = -std=c++20
tendril_LDFLAGS  = -static-libgcc -static-libstdc++ -pthread
tendril_LDADD    = -lrdkafka++
