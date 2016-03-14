#ifndef MONITOR_H
#define MONITOR_H

#include <queue>
#include <string>
#include <set>
#include <map>
#include "action.h"
#include "synchronization.h"
#include "communicator.h"

class action;

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
