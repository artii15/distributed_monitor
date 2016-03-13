#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "synchronization_request.h"
#include "monitor.h"

class communicator {
	public:
		virtual void send(synchronization_request*, process_id) = 0;
		virtual void send(synchronization_request*, std::set<process_id>) = 0;
};

#endif
