#include "../../inc/example/producer_action.h"

producer_action::producer_action(buffer<uint8_t>* buf) {
	this->buf = buf;
}

void producer_action::perform(monitor* mon) {
	while(buf->count() == buf->capacity()) {
		mon->wait();
	}

	buf->insert_at(buf->find_index_of(0), 1);
}
