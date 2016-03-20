#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "messages/sync_request.h"
#include "messages/frame.h"
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
		void send_lock_request(uint16_t critical_section_id, pthread_mutex_t* mutex);
		virtual void listen();
		void handle(sync_request* request);

	protected:
		virtual void broadcast_message(frame* message) = 0;
		virtual frame* receive_message() = 0;

		uint32_t time;
		uint32_t process_id;
		unsigned int number_of_processes;

	private:
		std::map<uint16_t, std::priority_queue<sync_request, std::vector<sync_request>, std::greater<sync_request> > > lock_requests;
		std::map<sync_request, request_descriptor> requests_descriptors;
};

#endif
