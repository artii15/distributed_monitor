#ifndef MONITOR_H
#define MONITOR_H

#include <queue>
#include <string>
#include <set>
#include <map>
#include "communicator.h"
#include "action.h"
#include "synchronization_request.h"

class action;
class communicator;

class monitor {
	public:
		monitor(communicator*);
		void call(action*);
		void wait();
		void signal();

	private:
		communicator* comm;

		void lock();
		void unlock();		
};

#endif
