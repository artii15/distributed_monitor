#ifndef RELEASE_SIGNAL_H
#define RELEASE_SIGNAL_H

#include "lock_request.h"

class release_signal: public packet {
	public:
		lock_request released_request;

		release_signal();
		release_signal(const lock_request*);

		virtual ~release_signal();
	protected:
		virtual size_t calculate_size();
		virtual void pack_into_buffer(uint8_t* buf);
		virtual void unpack_from_buffer(uint8_t* buf);
};

#endif
