#ifndef SYNCHRONIZER_H
#define SYNCHRONIZER_H

#include <map>
#include <set>
#include <pthread.h>
#include "request_descriptor.h"
#include "message_handler.h"
#include "messages/lock_request.h"
#include "messages/lock_response.h"
#include "messages/release_signal.h"
#include "messages/wait_signal.h"
#include "messages/wake_signal.h"
#include "communicator.h"
#include "process_descriptor.h"

class communicator;
class synchronizer: public message_handler {
	public:
		synchronizer(communicator*, process_descriptor*);
		void handle(uint8_t* raw_message, uint16_t tag);

		void wake_all_in_section(uint16_t critical_section_id);
		void wake_one_in_section(uint16_t critical_section_id);
		void wait_in_section(uint16_t critical_section_id, pthread_mutex_t* mutex);
		void release_section(uint16_t critical_section_id);
		void lock_section(uint16_t critical_section_id, pthread_mutex_t* waiting_process_mutex);
	
	private:
		communicator* comm;
		process_descriptor* process;

		std::map<uint16_t, std::set<lock_request> > lock_requests;
		std::map<lock_request, request_descriptor> requests_descriptors;
		std::map<uint16_t, const lock_request*> own_requests;

		std::map<uint16_t, std::set<wait_signal> > wait_signals;
		std::map<wait_signal, pthread_mutex_t*> wait_signals_mutexes;
		std::map<uint16_t, const wait_signal*> own_wait_signals;

		void try_to_enter(uint16_t critical_section_id);
		void request_critical_section_access(uint16_t critical_section_id, pthread_mutex_t* waiting_process_mutex);

		void handle(lock_request* request);
		void handle(lock_response* response);
		void handle(release_signal* signal);
		void handle(wait_signal* signal);
		void handle(wake_signal* signal);
};

#endif
