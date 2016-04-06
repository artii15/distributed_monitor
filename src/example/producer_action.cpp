#include "../../inc/example/producer_action.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>

producer_action::producer_action(buffer* buf) {
	this->buf = buf;
}

void producer_action::perform(monitor* mon) {
	while(buf->count() == buf->capacity()) {
		mon->wait();
	}

	buf->insert_at(buf->find_index_of(0), 1);

	std::ostringstream ss;
	ss << "Producer buffer state:";

	unsigned buf_size = buf->capacity();
	for(unsigned i = 0; i < buf_size; ++i) {
		ss << ' ' << buf->read_element(i);
	}

	printf("%s\n", ss.str().c_str());
}
