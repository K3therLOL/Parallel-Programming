//
// Created by Kether on 30.09.2024.
//
#include "../include/max.h"
#include "../include/randomaizer.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

/* Timing max function */
double time_max(int *arr, size_t size, int threads)
{
    double beg, end;

    beg = omp_get_wtime();
    max(arr, size, threads);
    end = omp_get_wtime();

    return end - beg;
}

/* Timing the algorithm */
#define test_it 10

void time_algorithm(void)
{
    const size_t sz = 300000000ULL;
    int *arr = (int *)malloc(sz * sizeof(int));

    for(int proc = 1; proc <= omp_get_num_procs(); ++proc)
    {
        double res = 0.0;
        for(int i = 1; i <= test_it; ++i)
        {
            arr = rand_array(arr, sz, i);
            res += time_max(arr, sz, proc);
        }
        res /= (double)test_it;
        printf("<%d threads> -- %.4lf sec\n", proc, res);
    }
    free(arr);
}