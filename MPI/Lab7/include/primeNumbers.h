#ifndef PRIME_NUMBERS_H
#define PRIME_NUMBERS_H

#include <mpi.h>

int *prime_numbers_package(int *, int *, int, int, MPI_Comm, int);

#endif
