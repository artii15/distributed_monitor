#ifndef MONITOR_H
#define MONITOR_H

#include <queue>
#include <set>
#include "action.h"
#include "synchronization_request.h"

class action;

typedef unsigned int process_id;
typedef unsigned long long timestamp;

class monitor {
	public:
		monitor(process_id id);
		void call(action*);
		void wait();
		void signal();

	private:
		process_id id;
		timestamp time;
		std::set<process_id> processes_ids;
		std::priority_queue<synchronization_request, std::vector<synchronization_request>, std::greater<synchronization_request> > lock_requests;
		std::priority_queue<synchronization_request, std::vector<synchronization_request>, std::greater<synchronization_request> > waiting_processes;

		void lock();
		void unlock();		
		void register_process(process_id);
};

#endif
