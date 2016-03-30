#ifndef MONITOR_H
#define MONITOR_H

#include "communicator.h"
#include "action.h"

class action;
class communicator;

class monitor {
	public:
		monitor(communicator*, uint16_t critical_section_id);
		void call(action*);
		void call(void (*)(monitor*));
		void wait();
		void notify();
		void notifyAll();

	private:
		communicator* comm;
		uint16_t critical_section_id;

		void lock();
		void unlock();		
};

#endif
