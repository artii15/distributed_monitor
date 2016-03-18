#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "synchronization_request.h"
#include "monitor.h"
#include <string>
#include <map>
#include <queue>

enum request_tag {
	LOCK_REQUEST = 1
};

class communicator {
	public:
		void sendLockRequest(uint16_t guarded_section_id, pthread_mutex_t* mutex);
		virtual void listen() = 0;
	protected:
		virtual void broadcastSyncRequest(uint16_t guarded_section_id, request_tag tag) = 0;

		std::map<std::string, std::priority_queue<synchronization_request, std::vector<synchronization_request>, std::greater<synchronization_request> > > lock_requests;
		std::map<std::string, std::priority_queue<synchronization_request, std::vector<synchronization_request>, std::greater<synchronization_request> > > waiting_processes;
};

#endif
