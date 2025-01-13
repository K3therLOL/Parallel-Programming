//
// Created by Asus on 19.12.2024.
//

#include <stdio.h>
#include <mpi.h>

void check_mpi_version(void)
{
    int version, subversion;
    MPI_Get_version(&version, &subversion);

    printf("MPI version %d.%d\n", version, subversion);
}