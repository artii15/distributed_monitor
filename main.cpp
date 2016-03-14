#include "inc/monitor.h"
#include "inc/communicator_stub.h"
#include "inc/action_stub.h"
#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	MPI_Init(NULL, NULL);

	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	cout << "Hello world from " << world_rank << endl
		<< "Number of processes: " << world_size << endl;

	MPI_Finalize();
}
