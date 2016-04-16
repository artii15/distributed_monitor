#include "../../inc/example/producer_action.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>

producer_action::producer_action(buffer* buf, uint32_t producer_id) {
	this->buf = buf;
	this->producer_id = producer_id;
}

void producer_action::perform(monitor* mon) {
	while(buf->count() == buf->capacity()) {
		mon->wait();
	}

	unsigned buf_size = buf->capacity();

	std::ostringstream status;
	status << "Producer " << producer_id << " buffer version: " << buf->version << ", elements count: " << buf->count() << ", content: ";

	for(unsigned i = 0; i < buf_size; ++i) {
		status << ' ' << buf->read_element(i);
	}

	printf("%s\n", status.str().c_str());

	buf->insert_at(buf->find_index_of(0), 1);

	mon->notify();
}
