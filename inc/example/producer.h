#ifndef PRODUCER_H
#define PRODUCER_H

#include "../monitor.h"
#include "buffer.hpp"

class producer {
	public:
		producer(buffer<uint8_t>*, monitor*);
		void run();
	private:
		buffer<uint8_t>* buf;
		monitor* mon;
};

#endif
