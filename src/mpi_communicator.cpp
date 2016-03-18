#include "../inc/mpi_communicator.h"
#include <mpi.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

mpi_communicator::mpi_communicator(uint32_t process_id, unsigned int number_of_processes) {
	this->process_id = process_id;
	this->number_of_processes = number_of_processes;
	time = 0;
	listening = false;
}

void mpi_communicator::broadcastSyncRequest(uint16_t tag) {
/*
	request->time = time;

	char* serialized_request = request->serialize();
	for(unsigned int process_id = 0; process_id < number_of_processes; ++process_id) {
		if(process_id != this->process_id) {
			MPI_Send(serialized_request, synchronization_request::size, MPI_BYTE, process_id, request->tag, MPI_COMM_WORLD);
		}
	}

	++time;
	free(serialized_request);
	*/
}

void mpi_communicator::listen() {
	listening = true;

	while(listening) {
		wait_for_message();
	}
}

void mpi_communicator::wait_for_message() {
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
