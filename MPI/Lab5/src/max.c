//
// Created by Asus on 19.12.2024.
//

#include <mpi.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>


int max(int *arr, int size)
{
    int rk;
    MPI_Comm_rank(MPI_COMM_WORLD, &rk);
    printf("rank = %d\n", rk);

    int pid, np;
    int elements_per_process, elements_recieved;

    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    int max = INT_MIN;

    if (pid == 0)
    {
        int index, i;
        elements_per_process = size / np;

        if (np > 1) {
            for (i = 1; i < np - 1; i++)
            {
                index = i * elements_per_process;

                MPI_Send(&elements_per_process, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
                MPI_Send(&arr[index], elements_per_process, MPI_INT, i, 0, MPI_COMM_WORLD);
            }

            // last process adds remaining elements
            index = i * elements_per_process;
            int elements_left = size - index;

            MPI_Send(&elements_left,
                     1, MPI_INT,
                     i, 0,
                     MPI_COMM_WORLD);
                     MPI_Send(&arr[index],
                     elements_left,
                     MPI_INT, i, 0,
                     MPI_COMM_WORLD);
        }
        else
        {
        }
        // master process add its own sub array
        for (i = 0; i < elements_per_process; i++)
            max = (arr[i] > max) ? arr[i] : max;

        // collects partial sums from other processes
        for (i = 1; i < np; i++)
        {
            int local_max;
            MPI_Recv(&local_max,1,MPI_INT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD, &status);

            max = (local_max > max) ? local_max : max;
        }

    }
    // child processes
    else
    {
        MPI_Recv(&elements_recieved,1, MPI_INT, 0, 0,MPI_COMM_WORLD, &status);

        int *buf = (int *)malloc(elements_recieved * sizeof(int));
        if(buf == NULL) {
            perror("");
            return INT_MIN;
        }
        else
        {
        }
        // stores the received array segment
        // in local array a2
        MPI_Recv(buf, elements_recieved,MPI_INT, 0, 0,MPI_COMM_WORLD, &status);

        // calculates its partial sum
        int local_max = INT_MIN;
        for (int i = 0; i < elements_recieved; i++)
            local_max = (buf[i] > local_max) ? buf[i] : local_max;

        // sends the partial sum to the root process
        MPI_Send(&local_max, 1, MPI_INT,0, 0, MPI_COMM_WORLD);
    }
    return max;
}