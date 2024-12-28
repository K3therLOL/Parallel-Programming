#include <mpi.h>
#include <stdlib.h>
#include "include/timeShellSort.h"



int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    if (time_algorithm() == false) {
        return EXIT_FAILURE;
    }

    MPI_Finalize();
}