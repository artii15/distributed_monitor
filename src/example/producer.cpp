#include "../../inc/example/producer.h"
#include <unistd.h>
#include <stdlib.h>

producer::producer(prod_cons_monitor* mon) {
	this->mon = mon;
}

void producer::run() {
	while(1) {
		mon->produce_element();
		//usleep(rand()%3000000);
	}
}
