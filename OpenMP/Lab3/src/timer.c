//
// Created by Kether on 20.10.2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "../include/randomaizer.h"
#include "../include/shellSort.h"

int get_timer_precision(void)
{
    int prec = 0;
    double tick = omp_get_wtick();

    tick = (tick > 0) ? tick : -tick;

    while(++prec && tick < 1.) {
        tick *= 10;
    }

    return prec;
}

double time_sort(int *arr, size_t sz, int threads)
{
    double beg, end;
    beg = omp_get_wtime();
    shell_sort(arr, sz, threads);
    end = omp_get_wtime();

    return end - beg;
}


#define over_proc 4

#define test_it 10

bool time_algorithm(void)
{
    const size_t size = 5000000ULL;

    int *arr = (int *)malloc(size * sizeof(int));
    if(NULL == arr) {
        return false;
    }

    int procs = omp_get_num_procs() + over_proc;
    for (int proc = 1; proc <= procs; ++proc)
    {
        double res = 0.0;
        for(int i = 0; i < test_it; ++i)
        {
            arr  = rand_array(arr, size, i);
            res += time_sort(arr, size, proc);
        }
        res /= (double)test_it;
        printf("<%d thread> -- %.*f sec\n", proc, get_timer_precision(), res);
    }

    return true;
}
