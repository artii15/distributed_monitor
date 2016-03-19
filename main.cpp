#include "inc/monitor.h"
#include "inc/mpi_communicator.h"
#include "inc/messages/sync_request.h"
#include "inc/messages/frame.h"
#include <mpi.h>
#include <iostream>

using namespace std;

void initialize();
void clean();

int main(int argc, char** argv) {
	initialize();

	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

		// sync_request(uint32_t process_id, uint32_t creation_time, uint16_t critical_section_id);
		// frame(uint32_t time, uint8_t tag, serializable* payload);
	sync_request  r(100, 200, 300);
	frame  m(1, 10, &r);

	cout << m.get_size() << endl;

	uint8_t serialized[m.get_size()];
	m.serialize(serialized);

	frame m2;
	sync_request r2;

	m2.payload = &r2;
	m2.deserialize(serialized);

	cout << m2.time << ' ' << m2.tag << ' ' << endl;
	
	cout << r2.process_id << ' ' << r2.creation_time << ' ' << r2.critical_section_id << endl;

	mpi_communicator comm(world_rank, world_size);

	clean();
}

void initialize() {
	MPI_Init(NULL, NULL);
}

void clean() {
	MPI_Finalize();
}
