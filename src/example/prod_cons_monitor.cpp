#include "../../inc/example/prod_cons_monitor.h"

prod_cons_monitor::prod_cons_monitor(synchronizer* processes_synchronizer, resources_synchronizer* res_synchronizer, buffer<uint8_t>* buf): monitor(processes_synchronizer, res_synchronizer, 1), prod_action(buf) {
			
}
