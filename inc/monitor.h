#ifndef MONITOR_H
#define MONITOR_H

#include <queue>
#include <list>
#include "action.h"
#include "synchronization_request.h"

class action;

typedef unsigned int process_id;

class monitor {
	public:
		void call(action*);
		void wait();
		void signal();

	private:
		std::priority_queue<synchronization_request, std::vector<synchronization_request>, std::greater<synchronization_request> > lock_requests;
		std::priority_queue<synchronization_request, std::vector<synchronization_request>, std::greater<synchronization_request> > waiting_processes;
		std::list<process_id> processes_ids;

		void lock();	
		void unlock();		
};

#endif
