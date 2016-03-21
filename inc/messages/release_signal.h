#ifndef RELEASE_SIGNAL_H
#define RELEASE_SIGNAL_H

#include "lock_request.h"

class release_signal: public packet {
	public:
		lock_request released_request;

		release_signal();
		release_signal(lock_request*);

		void serialize(uint8_t* buf);
		void deserialize(uint8_t* serialized);
		size_t get_size();

		virtual void be_handled_by(communicator*);

		virtual ~release_signal();
};

#endif
