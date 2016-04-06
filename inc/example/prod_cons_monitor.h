#ifndef PROD_CONS_MONITOR_H
#define PROD_CONS_MONITOR_H

#include "../monitor.h"
#include "buffer.hpp"
#include "producer_action.h"
#include "consumer_action.h"

class prod_cons_monitor: public monitor {
	public:
		prod_cons_monitor(synchronizer* processes_synchronizer, resources_synchronizer* res_synchronizer, buffer* buf, uint32_t id);

		void produce_element();
		void consume_element();
	private:
		producer_action prod_action;
		consumer_action cons_action;
};

#endif
