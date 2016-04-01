#ifndef SYNCHRONIZER_H
#define SYNCHRONIZER_H

#include "message_listener.h"

class synchronizer: public message_listener {
	public:
		virtual void on_message(frame*);
};

#endif
