//
// Created by Asus on 19.12.2024.
//
#include "../include/max.h"
#include "../include/randomaizer.h"
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <stdbool.h>

/* Timing max function */
static double time_max(int *arr, size_t size)
{
    double beg, end, res = -1.0;
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0) {
        beg = MPI_Wtime();
    }

    MPI_Barrier(MPI_COMM_WORLD);
    max(arr, size);
    MPI_Barrier(MPI_COMM_WORLD);

    if(rank == 0) {
        end = MPI_Wtime();
        res = end - beg;
    }

    return res;
}

static int resolution(void)
{
    double tick = MPI_Wtick();
    int res = 0;
    if(tick <= DBL_EPSILON) {
        return res;
    }

    while(tick < 1.0) {
        res++;
        tick *= 10;
    }

    return res;
}

/* Timing the algorithm */
#define NUM_IT 10

bool time_algorithm(void)
{
    int np, rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    const int sz = 300000000;
    int *arr = NULL;
    if(rank == 0 && (arr = (int *)malloc(sz * sizeof(int))) == NULL) {
        perror("");
        return false;
    }

    double res = 0.0;
    for(int i = 1; i <= NUM_IT; ++i)
    {
        if(rank == 0) {
            arr = rand_array(arr, sz, i);
        }

        double local_res = time_max(arr, sz);

        if(rank == 0) {
            res += local_res;
        }
    }

    if(rank == 0)
    {
        res /= (double)NUM_IT;
        printf("<%d threads> --- %.*lf sec\n", np, resolution(), res);
        free(arr);
    }

    return true;
}