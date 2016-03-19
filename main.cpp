#include "inc/monitor.h"
#include "inc/request_descriptor.h"
#include "inc/mpi_communicator.h"
#include "inc/synchronization_request.h"
#include <mpi.h>
#include <map>
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

	synchronization_request r1, r2;
	map<synchronization_request, request_descriptor> desc;

	//desc[r1] = request_descriptor(r1, NULL, 0);


	mpi_communicator comm(world_rank, world_size);

	clean();
}

void initialize() {
	MPI_Init(NULL, NULL);
}

void clean() {
	MPI_Finalize();
}
