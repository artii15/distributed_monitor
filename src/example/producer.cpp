#include "../../inc/example/producer.h"
#include <unistd.h>
#include <stdlib.h>

producer::producer(buffer<uint8_t>* buf, prod_cons_monitor* mon) {
	this->buf = buf;
	this->mon = mon;
}

void producer::run() {
	while(1) {
		mon->produce_element();
		usleep(rand()%3000000);
	}
}
