#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "synchronization_request.h"
#include "monitor.h"
#include "guarded_section_descriptor.h"
#include <map>
#include <queue>

typedef struct REQUEST_TAG {
	const static uint16_t LOCK_REQUEST = 1;
} REQUEST_TAG;

class communicator {
	public:
		communicator(uint32_t process_id, unsigned int number_of_processes);
		void send_lock_request(guarded_section_descriptor);
		virtual void listen() = 0;

	protected:
		virtual void broadcast_sync_request(synchronization_request* request) = 0;

		uint32_t time;
		uint32_t process_id;
		unsigned int number_of_processes;

	private:
		std::map<uint16_t, std::priority_queue<pending_request*, std::vector<synchronization_request>, std::greater<synchronization_request> > > lock_requests;
		std::map<uint16_t, std::priority_queue<pending_request*, std::vector<synchronization_request>, std::greater<synchronization_request> > > waiting_processes;
};

#endif
