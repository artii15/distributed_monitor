#include "../../../inc/synchronizer/messages/wake_signal.h"

wake_signal::wake_signal() {}

wake_signal::wake_signal(uint8_t* buf) {
	deserialize(buf);
}

wake_signal::wake_signal(uint16_t tag, uint32_t time, const wait_signal* signal_to_release): synchronization_message(tag, time) {
	this->signal_to_release = *signal_to_release;
}

void wake_signal::serialize_synchronization_members(uint8_t* buf) {
	signal_to_release.serialize(buf);
}

void wake_signal::deserialize_synchronization_members(uint8_t* serialized) {
	signal_to_release.deserialize(serialized);
}

size_t wake_signal::calculate_synchronization_members_size() {
	return signal_to_release.get_size();
}

wake_signal::~wake_signal() {}
