#include "../../inc/example/prod_cons_monitor.h"

prod_cons_monitor::prod_cons_monitor(synchronizer* processes_synchronizer, resources_synchronizer* res_synchronizer, buffer* buf, uint32_t id): 
	monitor(processes_synchronizer, res_synchronizer, 1), prod_action(buf), cons_action(buf, id) {
				
}

void prod_cons_monitor::produce_element() {
	this->call(&prod_action);
}

void prod_cons_monitor::consume_element() {
	this->call(&cons_action);
}
