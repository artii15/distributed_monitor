#ifndef PROD_CONS_MONITOR_H
#define PROD_CONS_MONITOR_H

#include "../monitor.h"
#include "buffer.hpp"

class prod_cons_monitor: public monitor {
	public:
		prod_cons_monitor(synchronizer* processes_synchronizer, resources_synchronizer* res_synchronizer);
};

#endif
