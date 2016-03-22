#ifndef RELEASE_SIGNAL_H
#define RELEASE_SIGNAL_H

#include "lock_request.h"

class release_signal: public packet {
	public:
		lock_request released_request;

		release_signal();
		release_signal(const lock_request*);

		virtual void serialize(uint8_t* buf);
		virtual void deserialize(uint8_t* serialized);
		virtual size_t get_size();

		virtual void be_handled_by(communicator*);

		virtual ~release_signal();
};

#endif
