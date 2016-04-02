#include "../../inc/messages/wake_signal.h"

wake_signal::wake_signal() {}

wake_signal::wake_signal(const wait_signal* signal_to_release) {
	this->signal_to_release = *signal_to_release;
}

void wake_signal::pack_into_buffer(uint8_t* buf) {
	signal_to_release.pack_into_buffer(buf);
}

void wake_signal::unpack_from_buffer(uint8_t* serialized) {
	signal_to_release.unpack_from_buffer(serialized);
}

size_t wake_signal::calculate_size() {
	return signal_to_release.calculate_size();
}

wake_signal::~wake_signal() {}
