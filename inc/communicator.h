#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "synchronization.h"
#include "monitor.h"

class communicator {
	public:
		virtual void broadcast(synchronization_request*) = 0;
};

#endif
