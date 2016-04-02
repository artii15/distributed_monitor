#ifndef WAIT_SIGNAL_H
#define WAIT_SIGNAL_H

#include "lock_request.h"

class wait_signal: public packet {
	public:
		lock_request request_to_remove;

		wait_signal();
		wait_signal(const lock_request*);

		bool operator>(const wait_signal& signal) const;
		bool operator==(const wait_signal& signal) const;
		bool operator<(const wait_signal& signal) const;

		virtual ~wait_signal();
	protected:
		virtual size_t calculate_size();
		virtual void pack_into_buffer(uint8_t* buf);
		virtual void unpack_from_buffer(uint8_t* buf);
};

#endif
