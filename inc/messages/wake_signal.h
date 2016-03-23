#ifndef WAKE_SIGNAL_H
#define WAKE_SIGNAL_H

#include "wait_signal.h"

class wake_signal: public packet {
	public:
		wait_signal signal_to_release;

		wake_signal();
		wake_signal(const wait_signal*);

		virtual void serialize(uint8_t* buf);
		virtual void deserialize(uint8_t* serialized);
		virtual size_t get_size();

		virtual void be_handled_by(communicator*);

		virtual ~wake_signal();
};

#endif
