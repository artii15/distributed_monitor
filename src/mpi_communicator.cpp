#include "../inc/mpi_communicator.h"
#include "../inc/synchronization_request_mpi_type.h"
#include <mpi.h>

mpi_communicator::mpi_communicator(int rank, int number_of_processes) {
	this->rank = rank;
	this->number_of_processes = number_of_processes;
	time = 0;

}

void mpi_communicator::broadcast(synchronization_request* request) {
	for(int process_rank = 0; process_rank < number_of_processes; ++process_rank) {
		MPI_Send(request, 1, synchronization_request_mpi_type::instance->getType(), process_rank, request->tag, MPI_COMM_WORLD);
	}
}

void mpi_communicator::listen() {
	synchronization_request request;
	MPI_Status status;

	MPI_Recv(&request, 1, synchronization_request_mpi_type::instance->getType(), MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
}
