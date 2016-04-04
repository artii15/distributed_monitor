#ifndef MONITOR_H
#define MONITOR_H

#include "synchronizer/synchronizer.h"
#include "resources_synchronizer/resources_synchronizer.h"
#include "action.h"

class monitor {
	public:
		monitor(synchronizer* processes_synchronizer, resources_synchronizer* res_synchronizer, uint16_t critical_section_id);
		void call(action*);
		void call(void (*)(monitor*));
		void wait();
		void notify();
		void notify_all();

	private:
		synchronizer* proc_synchronizer;
		resources_synchronizer* res_synchronizer;
		uint16_t critical_section_id;

		void lock();
		void unlock();
};

#endif
