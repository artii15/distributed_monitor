#ifndef PRODUCER_H
#define PRODUCER_H

#include "prod_cons_monitor.h"
#include "buffer.hpp"

class producer {
	public:
		producer(buffer<uint8_t>*, prod_cons_monitor*);
		void run();
	private:
		buffer<uint8_t>* buf;
		prod_cons_monitor* mon;
};

#endif
