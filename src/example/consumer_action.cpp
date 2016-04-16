#include "../../inc/example/consumer_action.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>

consumer_action::consumer_action(buffer* buf, uint32_t consumer_id) {
	this->buf = buf;
	this->consumer_id = consumer_id;
}

void consumer_action::perform(monitor* mon) {
	while(buf->count() == 0) {
		mon->wait();
	}

	unsigned buf_size = buf->capacity();

	std::ostringstream status;
	status << "Consumer " << consumer_id << " buffer version: " << buf->version << ", elements count: " << buf->count() << ", content: ";

	for(unsigned i = 0; i < buf_size; ++i) {
		status << ' ' << buf->read_element(i);
	}

	printf("%s\n", status.str().c_str());

	buf->remove_from(buf->find_index_of(1), 0);

	mon->notify();
}
