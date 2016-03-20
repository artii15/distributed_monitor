#ifndef PACKET_H
#define PACKET_H

#include "serializable.h"

class communicator;

class packet: public serializable {
	public:
		virtual void be_handled_by(communicator*) = 0;
};

#endif
