#https://stackoverflow.com/questions/70584133/when-using-libadd-in-automake-libtool-links-incorrectly
# might need this for windows linking -> libbar_la_LDFLAGS += -no-undefined
bin_PROGRAMS  = tendril
tendril_SOURCES  = main.cpp tendril.cpp tendril_queue_manager.cpp tendril_network_server.cpp
tendril_CPPFLAGS = -std=c++20
tendril_LDFLAGS  = -static-libgcc -static-libstdc++ -pthread
tendril_LDADD    = -lrdkafka++
