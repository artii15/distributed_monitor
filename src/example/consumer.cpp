#include "../../inc/example/consumer.h"
#include <unistd.h>
#include <stdlib.h>

consumer::consumer(prod_cons_monitor* mon) {
	this->mon = mon;
}

void consumer::run() {
	while(1) {
		mon->consume_element();
		//usleep(rand()%3000000);
	}
}
