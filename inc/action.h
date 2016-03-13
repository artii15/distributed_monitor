#ifndef ACTION_H
#define ACTION_H

#include "monitor.h"

class monitor;

class action {
	public:
		virtual void perform(monitor*) = 0;	
};

#endif
