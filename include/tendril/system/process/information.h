#ifndef __TENDRIL__SYSTEM__PROCESS__INFORMATION__H
#define __TENDRIL__SYSTEM__PROCESS__INFORMATION__H
//https://man7.org/linux/man-pages/man5/proc.5.html
// https://www.linuxjournal.com/article/6799
namespace tendril::system::process {
	void set_cpu_affinity(unsigned long pid);
}
#endif