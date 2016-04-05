#ifndef CONSUMER_H
#define CONSUMER_H

#include "prod_cons_monitor.h"
#include "buffer.hpp"

class consumer {
	public:
		consumer(buffer<uint8_t>*, prod_cons_monitor*);
		void run();
	private:
		buffer<uint8_t>* buf;
		prod_cons_monitor* mon;
};

#endif
