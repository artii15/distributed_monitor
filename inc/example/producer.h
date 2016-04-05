#ifndef PRODUCER_H
#define PRODUCER_H

#include "prod_cons_monitor.h"

class producer {
	public:
		producer(prod_cons_monitor*);
		void run();
	private:
		prod_cons_monitor* mon;
};

#endif
