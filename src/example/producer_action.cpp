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

	unsigned buf_size = buf->capacity();

	std::ostringstream ss1;
	ss1 << "Producer 0 buffer state: version " << buf->version << " count " << buf->count();

	for(unsigned i = 0; i < buf_size; ++i) {
		ss1 << ' ' << buf->read_element(i);
	}

	printf("%s\n", ss1.str().c_str());

	buf->insert_at(buf->find_index_of(0), 1);

	mon->notify();
}
