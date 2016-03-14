#include "../inc/synchronization_request_mpi_type.h"
#include "synchronization.h"

synchronization_request_mpi_type::synchronization_request_mpi_type() {
    const int nitems = 3;
	int blocklengths[nitems] = {1, 1, 1};
    MPI_Datatype types[nitems] = {MPI_INT, MPI_UNSIGNED_LONG_LONG, MPI_INT};
    MPI_Aint offsets[nitems];

    offsets[0] = offsetof(synchronization_request, time);
    offsets[1] = offsetof(synchronization_request, pid);
    offsets[2] = offsetof(synchronization_request, tag);

    MPI_Type_create_struct(nitems, blocklengths, offsets, types, &type);
    MPI_Type_commit(&type);
}

synchronization_request_mpi_type::~synchronization_request() {
	MPI_Type_free(&type);
}

synchronization_request_mpi_type* synchronization_request_mpi_type::getType() {
	return &type;
}
