#ifndef PACKET_H
#define PACKET_H

#include "serializable.h"

class communicator;

class packet: public serializable {
	public:
		void be_handled_by(communicator*);
}

#endif
