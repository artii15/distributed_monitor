#ifndef WAKE_SIGNAL_H
#define WAKE_SIGNAL_H

#include "wait_signal.h"

class wake_signal: public packet {
	public:
		wait_signal signal_to_release;

		wake_signal();
		wake_signal(const wait_signal*);

		virtual size_t calculate_size();
		virtual void pack_into_buffer(uint8_t* buf);
		virtual void unpack_from_buffer(uint8_t* buf);

		virtual ~wake_signal();
};

#endif
