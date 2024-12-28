//
// Created by Asus on 25.12.2024.
//
#include <float.h>
#include <mpi.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/randomaizer.h"
#include "../include/shellSort.h"

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

static double time_shell_sort(int *array, int size)
{
    double start, end, res = -1.0;
    int rk;
    MPI_Comm_rank(MPI_COMM_WORLD, &rk);
    if (rk == 0) {
        start = MPI_Wtime();
    }

    shell_sort(array, size);

    if (rk == 0) {
        end = MPI_Wtime();
        res = end - start;
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

    const int sz = 10000000;
    int *arr = NULL;
    if(rank == 0 && (arr = (int *)malloc(sz * sizeof(int))) == NULL) {
        perror("");
        return false;
    }

    double res = 0.0;
    for(int i = 1; i <= NUM_IT; ++i)
    {
        if(rank == 0) {
            rand_array(&arr, sz);
        }

        double local_res = time_shell_sort(arr, sz);

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