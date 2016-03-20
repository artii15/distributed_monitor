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

	mpi_communicator comm(world_rank, world_size);

	clean();
}

void initialize() {
	MPI_Init(NULL, NULL);
}

void clean() {
	MPI_Finalize();
}
