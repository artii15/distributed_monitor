#ifndef PRODUCER_ACTION_H
#define PRODUCER_ACTION_H

#include "../action.h"
#include "buffer.hpp"

class producer_action: public action {
	public:
		producer_action(buffer<uint8_t>*);

		virtual void perform(monitor*);
	private:
		buffer<uint8_t>* buf;
};

#endif
