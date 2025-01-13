#include "include/primeNumbers.h"
#include <omp.h>
#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int sz, rk;
    MPI_Comm_size(MPI_COMM_WORLD, &sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &rk);
    
    
    MPI_Finalize();
}

