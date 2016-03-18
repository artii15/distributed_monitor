#ifndef MONITOR_H
#define MONITOR_H

#include "communicator.h"
#include "action.h"
#include "synchronization_request.h"

class action;
class communicator;

class monitor {
	public:
		monitor(communicator*, uint16_t guarded_section_id);
		void call(action*);
		void wait();
		void signal();

	private:
		communicator* comm;
		uint16_t guarded_section_id;

		void lock();
		void unlock();		
};

#endif
