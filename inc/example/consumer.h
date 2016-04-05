#ifndef CONSUMER_H
#define CONSUMER_H

#include "prod_cons_monitor.h"

class consumer {
	public:
		consumer(prod_cons_monitor*);
		void run();
	private:
		prod_cons_monitor* mon;
};

#endif
