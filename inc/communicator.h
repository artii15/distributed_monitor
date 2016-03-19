#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "synchronization_request.h"
#include "request_descriptor.h"
#include "monitor.h"
#include <pthread.h>
#include <map>
#include <queue>

typedef struct REQUEST_TAG {
	const static uint16_t LOCK_REQUEST = 1;
} REQUEST_TAG;

class communicator {
	public:
		bool enabled;
		communicator(uint32_t process_id, unsigned int number_of_processes);
		void send_lock_request(uint16_t guarded_section_id, pthread_mutex_t* mutex);
		virtual void listen();

	protected:
		virtual void broadcast_sync_request(synchronization_request* request) = 0;
		virtual void receive_message(synchronization_request* message) = 0;

		uint32_t time;
		uint32_t process_id;
		unsigned int number_of_processes;

	private:
		std::map<uint16_t, std::priority_queue<synchronization_request, std::vector<synchronization_request>, std::greater<synchronization_request> > > lock_requests;
		std::map<synchronization_request, request_descriptor> requests_descriptors;

		void handle_message(synchronization_request* message);
		void handle_lock_request(synchronization_request* request);
};

#endif
