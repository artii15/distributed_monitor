#ifndef SYNCHRONIZER_H
#define SYNCHRONIZER_H

#include <map>
#include <set>
#include <pthread.h>
#include "request_descriptor.h"
#include "message_listener.h"
#include "messages/lock_request.h"
#include "messages/lock_response.h"
#include "messages/release_signal.h"
#include "messages/wait_signal.h"
#include "messages/wake_signal.h"

class synchronizer: public message_listener {
	public:
		virtual void on_message(frame*);
	
	private:
		std::map<uint16_t, std::set<lock_request> > lock_requests;
		std::map<lock_request, request_descriptor> requests_descriptors;
		std::map<uint16_t, const lock_request*> own_requests;

		std::map<uint16_t, std::set<wait_signal> > wait_signals;
		std::map<wait_signal, pthread_mutex_t*> wait_signals_mutexes;
		std::map<uint16_t, const wait_signal*> own_wait_signals;
};

#endif
