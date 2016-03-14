#ifndef MONITOR_H
#define MONITOR_H

#include <queue>
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
		
		std::priority_queue<synchronization_request, std::vector<synchronization_request>, std::greater<synchronization_request> > lock_requests;
		std::priority_queue<synchronization_request, std::vector<synchronization_request>, std::greater<synchronization_request> > waiting_processes;

		void lock();
		void unlock();		
};

#endif
