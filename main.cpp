#include "inc/monitor.h"
#include "inc/communicator_stub.h"
#include "inc/action_stub.h"

int main() {
	communicator_stub comm;
	monitor m(&comm);
	action_stub a;
	m.call(&a);

	return 0;	
}
