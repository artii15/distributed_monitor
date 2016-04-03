#include "inc/monitor.h"
#include "inc/mpi_communicator.h"
#include "inc/messages/lock_request.h"
#include <mpi.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#define THREADING_NOT_SUPPORTED 1

using namespace std;

communicator* comm;

void* listening_task(void* args) {
	comm->listen();	

	pthread_exit(NULL);
}

void test(monitor* m) {
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank == 0) {
		printf("I'll be waiting in a moment\n");
		m->wait();	
		printf("Just awaken\n");
	}
	else {
		printf("I'm going to wake one of processes\n");
		m->notify();
		printf("Just woken one of processes\n");
	}
}

int main(int argc, char** argv) {
	int provided_thread_support;
	MPI_Init_thread(NULL, NULL, MPI_THREAD_MULTIPLE, &provided_thread_support);
	if(provided_thread_support != MPI_THREAD_MULTIPLE) {
		MPI_Abort(MPI_COMM_WORLD, THREADING_NOT_SUPPORTED);
	}

	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	MPI_Comm duplicated_world_comm;
	MPI_Comm_dup(MPI_COMM_WORLD, &duplicated_world_comm);
	
	environment_descriptor env = { .process_id = (uint32_t)world_rank, .number_of_processes = (uint32_t)world_size };
	mpi_communicator mpi_comm(&env, &duplicated_world_comm);
	comm = &mpi_comm;

	pthread_t listening_thread;
	pthread_create(&listening_thread, NULL, listening_task, NULL);

	//monitor m(comm, 1);
	//m.call(test);

	pthread_join(listening_thread, NULL);

	MPI_Comm_free(&duplicated_world_comm);

	MPI_Finalize();
}
