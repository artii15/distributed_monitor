#ifndef MONITOR_H
#define MONITOR_H

#include "synchronizer/synchronizer.h"
#include "action.h"

class action;
class synchronizer;

class monitor {
	public:
		monitor(synchronizer* synchronizator, uint16_t critical_section_id);
		void call(action*);
		void call(void (*)(monitor*));
		void wait();
		void notify();
		void notify_all();

	private:
		synchronizer* synchronizator;
		uint16_t critical_section_id;

		void lock();
		void unlock();
};

#endif
