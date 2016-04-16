#include "../../inc/example/prod_cons_monitor.h"

#define BUFFER_CRITICAL_SECTION_ID 1

prod_cons_monitor::prod_cons_monitor(synchronizer* processes_synchronizer, resources_synchronizer* res_synchronizer, buffer* buf, uint32_t process_id): 
	monitor(processes_synchronizer, res_synchronizer, BUFFER_CRITICAL_SECTION_ID), prod_action(buf, process_id), cons_action(buf, process_id) {
				
}

void prod_cons_monitor::produce_element() {
	this->call(&prod_action);
}

void prod_cons_monitor::consume_element() {
	this->call(&cons_action);
}
