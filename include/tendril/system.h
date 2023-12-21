#ifndef __TENDRIL__SYSTEM__H
#define __TENDRIL__SYSTEM__H
#include <thread>
namespace tendril::system {
	auto max_threads = std::thread::hardware_concurrency();
}
#endif