#include "../../inc/messages/wake_signal.h"
#include "../../inc/communicator.h"

wake_signal::wake_signal() {}

wake_signal::wake_signal(const wait_signal* signal_to_release) {
	this->signal_to_release = *signal_to_release;
}

void wake_signal::serialize(uint8_t* buf) {
	signal_to_release.serialize(buf);
}

void wake_signal::deserialize(uint8_t* serialized) {
	signal_to_release.deserialize(serialized);
}

size_t wake_signal::get_size() {
	return signal_to_release.get_size();
}

void wake_signal::be_handled_by(communicator* comm) {
	comm->handle(this);
}

wake_signal::~wake_signal() {}
