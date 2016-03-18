#include "../inc/mpi_communicator.h"
#include <mpi.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

mpi_communicator::mpi_communicator(uint32_t process_id, unsigned int number_of_processes) {
	this->process_id = process_id;
	this->number_of_processes = number_of_processes;
	time = 0;
}

void mpi_communicator::broadcastSyncRequest(request_tag tag) {
	synchronization_request request(process_id, time, tag);

	char* serialized_request = request.serialize();
	for(unsigned int process_id = 0; process_id < number_of_processes; ++process_id) {
		if(process_id != this->process_id) {
			MPI_Send(serialized_request, synchronization_request::size, MPI_BYTE, process_id, tag, MPI_COMM_WORLD);
		}
	}

	++time;
	free(serialized_request);
}

void mpi_communicator::listen() {
	char* serialized_request = (char*)malloc(synchronization_request::size);

	MPI_Status status;
	MPI_Recv(serialized_request, synchronization_request::size, MPI_BYTE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	++time;

	synchronization_request request(serialized_request);
	free(serialized_request);

	handle_request(&request);
}

void mpi_communicator::handle_request(synchronization_request* request) {
		
}
