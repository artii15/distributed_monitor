#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "messages/frame.h"
#include "messages/lock_request.h"
#include "messages/lock_response.h"
#include "messages/release_signal.h"
#include "request_descriptor.h"
#include "monitor.h"
#include <pthread.h>
#include <map>
#include <set>

typedef struct MESSAGE_TAG {
	const static uint16_t LOCK_REQUEST = 1;
	const static uint16_t LOCK_RESPONSE = 2;
	const static uint16_t RELEASE_SIGNAL = 3;
} MESSAGE_TAG;

class communicator {
	public:
		bool enabled;
		communicator(uint32_t process_id, unsigned int number_of_processes);

		void send_lock_request(uint16_t critical_section_id, pthread_mutex_t* mutex);
		void send_release_signal(uint16_t critical_section_id);

		virtual void listen();
		void handle(lock_request* request);
		void handle(lock_response* response);
		void handle(release_signal* response);

		virtual ~communicator();

	protected:
		virtual void broadcast_message(frame* message) = 0;
		virtual void send_message(frame* message, uint32_t recipient_id) = 0;
		virtual frame* receive_message() = 0;

		uint32_t process_id;
		unsigned int number_of_processes;

	private:
		std::map<uint16_t, std::set<lock_request> > lock_requests;
		std::map<lock_request, request_descriptor> requests_descriptors;
		std::map<uint16_t, const lock_request*> own_requests;

		pthread_mutex_t internal_state_mutex = PTHREAD_MUTEX_INITIALIZER;
		uint32_t time;

		void try_to_enter(uint16_t critical_section_id);
};

#endif
