#include "../../inc/example/prod_cons_monitor.h"

prod_cons_monitor::prod_cons_monitor(synchronizer* processes_synchronizer, resources_synchronizer* res_synchronizer): monitor(processes_synchronizer, res_synchronizer, 1) {
			
}
