#ifndef CONSUMER_ACTION_H
#define CONSUMER_ACTION_H

#include "../action.h"
#include "buffer.hpp"

class consumer_action: public action {
	public:
		consumer_action(buffer<uint8_t>*);

		virtual void perform(monitor*);
	private:
		buffer<uint8_t>* buf;
};

#endif
