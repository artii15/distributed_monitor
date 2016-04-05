#include "../../inc/example/consumer_action.h"

consumer_action::consumer_action(buffer<uint8_t>* buf) {
	this->buf = buf;
}

void consumer_action::perform(monitor* mon) {
	while(buf->count() == 0) {
		mon->wait();
	}

	buf->remove_from(buf->find_index_of(1), 0);
}