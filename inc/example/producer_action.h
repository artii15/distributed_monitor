#ifndef PRODUCER_ACTION_H
#define PRODUCER_ACTION_H

#include "../action.h"
#include "buffer.hpp"

class producer_action: public action {
	public:
		producer_action(buffer*);

		virtual void perform(monitor*);
	private:
		buffer* buf;
};

#endif
