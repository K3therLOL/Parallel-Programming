#include <mpi.h>
#include "include/timeAlgorithm.h"

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    time_algorithm();

    MPI_Finalize();
}

