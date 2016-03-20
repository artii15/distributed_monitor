#include "../../inc/messages/packet.h"

void packet::be_handled_by(communicator* comm) {
	comm->handle(this);
}
