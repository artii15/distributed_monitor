#include "../inc/mpi_communicator.h"
#include <mpi.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

mpi_communicator::mpi_communicator(uint32_t process_id, unsigned int number_of_processes)
	: communicator(process_id) {
	this->number_of_processes = number_of_processes;
}

void mpi_communicator::broadcast_sync_request(synchronization_request* request) {
	char* serialized_request = request->serialize();
	for(unsigned int process_id = 0; process_id < number_of_processes; ++process_id) {
		if(process_id != this->process_id) {
			MPI_Send(serialized_request, request->size, MPI_BYTE, process_id, request->tag, MPI_COMM_WORLD);
		}
	}
	++time;
	free(serialized_request);
}

void mpi_communicator::listen() {
	char* serialized_request = (char*)malloc(synchronization_request::size);

	MPI_Status status;
	MPI_Recv(serialized_request, synchronization_request::size, MPI_BYTE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

	synchronization_request request(serialized_request);
	time = ((request.time > time) ? request.time : time) + 1;

	free(serialized_request);

	handle_request(&request);
}

void mpi_communicator::handle_request(synchronization_request* request) {
	switch(request->tag) {
		case REQUEST_TAG::LOCK_REQUEST: this->handle_lock_request(request); break;
	}
}

void mpi_communicator::handle_lock_request(synchronization_request* request) {
		
}
