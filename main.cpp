#include "inc/monitor.h"
#include "inc/action_stub.h"

int main() {
	monitor m(1);
	action_stub a;

	m.call(&a);

	return 0;	
}
