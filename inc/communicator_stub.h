#ifndef COMMUNICATOR_STUB_H
#define COMMUNICATOR_STUB_H

#include "communicator.h"

class communicator_stub: public communicator {
	public:
		virtual void broadcast(synchronization_request* request) {

		}
};

#endif
