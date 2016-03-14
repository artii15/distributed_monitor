#include "inc/monitor.h"
#include "inc/synchronization_request_mpi_type.h"
#include <mpi.h>
#include <iostream>

using namespace std;

void initialize();
void clean();

int main(int argc, char** argv) {
	initialize();

	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	clean();
}

void initialize() {
	MPI_Init(NULL, NULL);
	synchronization_request_mpi_type::instance = new synchronization_request_mpi_type();
}

void clean() {
	delete synchronization_request_mpi_type::instance;
	MPI_Finalize();
}
