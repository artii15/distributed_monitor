#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "synchronization_request.h"
#include "monitor.h"
#include "guarded_section_descriptor.h"
#include <string>
#include <map>
#include <queue>

enum request_tag {
	LOCK_REQUEST = 1
};

class communicator {
	public:
		communicator(uint32_t process_id);
		void send_lock_request(guarded_section_descriptor);
		virtual void listen() = 0;

	protected:
		virtual void broadcast_sync_request(synchronization_request* request) = 0;

		uint32_t time;
		uint32_t process_id;
		std::map<std::string, std::priority_queue<synchronization_request, std::vector<synchronization_request>, std::greater<synchronization_request> > > lock_requests;
		std::map<std::string, std::priority_queue<synchronization_request, std::vector<synchronization_request>, std::greater<synchronization_request> > > waiting_processes;
};

#endif
