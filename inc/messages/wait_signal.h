#ifndef WAIT_SIGNAL_H
#define WAIT_SIGNAL_H

#include "lock_request.h"

class wait_signal: public packet {
	public:
		lock_request request_to_remove;

		wait_signal();
		wait_signal(const lock_request*);

		virtual void serialize(uint8_t* buf);
		virtual void deserialize(uint8_t* serialized);
		virtual size_t get_size();

		virtual void be_handled_by(communicator*);

		virtual ~wait_signal();
};

#endif
