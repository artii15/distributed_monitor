#include "../../inc/example/producer.h"

producer::producer(buffer<uint8_t>* buf, monitor* mon) {
	this->buf = buf;
	this->mon = mon;
}

void producer::run() {
	while(1) {

	}
}
