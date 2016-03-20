#include "inc/monitor.h"
#include "inc/mpi_communicator.h"
#include "inc/messages/lock_request.h"
#include "inc/messages/frame.h"
#include <mpi.h>
#include <pthread.h>
#include <stdio.h>

using namespace std;

void initialize();
void clean();

communicator* comm;

void* listening_task(void* arg) {
	comm->listen();	

	pthread_exit(NULL);
}

int main(int argc, char** argv) {
	initialize();

	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	mpi_communicator mpi_comm(world_rank, world_size);
	comm = &mpi_comm;

	pthread_t listening_thread;
	pthread_create(&listening_thread, NULL, listening_task, NULL);

	getchar();

	clean();
}

void initialize() {
	MPI_Init(NULL, NULL);
}

void clean() {
	MPI_Finalize();
}
