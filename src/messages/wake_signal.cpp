#include "../../inc/messages/wake_signal.h"

wake_signal::wake_signal() {}

wake_signal::wake_signal(const wait_signal* signal_to_release) {
	this->signal_to_release = *signal_to_release;
}

void wake_signal::serialize_members(uint8_t* buf) {
	signal_to_release.serialize(buf);
}

void wake_signal::deserialize_members(uint8_t* serialized) {
	signal_to_release.deserialize(serialized);
}

size_t wake_signal::calculate_members_size() {
	return signal_to_release.get_size();
}

wake_signal::~wake_signal() {}
