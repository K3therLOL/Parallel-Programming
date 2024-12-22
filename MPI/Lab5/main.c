#include <mpi.h>
#include "include/MPIcheck.h"
#include "include/timeMax.h"

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0) {
        check_mpi_version();
    }

    time_algorithm();

    MPI_Finalize();
}