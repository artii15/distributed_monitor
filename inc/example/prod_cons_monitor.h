#ifndef PROD_CONS_MONITOR_H
#define PROD_CONS_MONITOR_H

#include "../monitor.h"
#include "buffer.hpp"
#include "producer_action.h"

class prod_cons_monitor: public monitor {
	public:
		prod_cons_monitor(synchronizer* processes_synchronizer, resources_synchronizer* res_synchronizer, buffer<uint8_t>* buf);
	private:
		producer_action prod_action;
};

#endif
