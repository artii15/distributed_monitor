#include "../../inc/example/consumer_action.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>

consumer_action::consumer_action(buffer* buf) {
	this->buf = buf;
}

void consumer_action::perform(monitor* mon) {
	while(buf->count() == 0) {
		mon->wait();
	}

	unsigned buf_size = buf->capacity();

	std::ostringstream ss1;
	ss1 << "Consumer buffer state: version " << buf->version;

	for(unsigned i = 0; i < buf_size; ++i) {
		ss1 << ' ' << buf->read_element(i);
	}

	printf("%s\n", ss1.str().c_str());

	buf->remove_from(buf->find_index_of(1), 0);

	std::ostringstream ss;
	ss << "Consumer buffer state: version " << buf->version;

	for(unsigned i = 0; i < buf_size; ++i) {
		ss << ' ' << buf->read_element(i);
	}

	printf("%s\n", ss.str().c_str());
}
