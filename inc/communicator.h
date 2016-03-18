#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "synchronization_request.h"
#include "monitor.h"
#include <string>
#include <map>
#include <queue>

class communicator {
	public:
		void sendLockRequest(pthread_mutex_t*);
		virtual void listen() = 0;
	protected:
		std::map<std::string, std::priority_queue<synchronization_request, std::vector<synchronization_request>, std::greater<synchronization_request> > > lock_requests;
		std::map<std::string, std::priority_queue<synchronization_request, std::vector<synchronization_request>, std::greater<synchronization_request> > > waiting_processes;
};

#endif
