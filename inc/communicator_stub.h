#ifndef COMMUNICATOR_STUB_H
#define COMMUNICATOR_STUB_H

#include "communicator.h"

class communicator_stub: public communicator {
	public:
		virtual void send(synchronization_request*, process_id) {

		}

		virtual void send(synchronization_request*, std::set<process_id>*) {

		}
};

#endif
