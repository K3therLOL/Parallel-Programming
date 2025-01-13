//
// Created by Kether on 15.10.2024.
//
#include <iso646.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

static void swap(int *x, int *y)
{
    int t = *x;
    *x = *y;
    *y = t;
}

static void insertion_sort(int *arr, size_t start, size_t sz, size_t step)
{
    for(size_t j = start + step; j < sz; j += step)
    {
        size_t k = j;
        while(k > start and arr[k - step] > arr[k])
        {
            swap(&arr[k - step], &arr[k]);
            k -= step;
        }
    }
}

#define MAX_STEPS 31

static size_t *sedgewick_steps(size_t sz, size_t *d)
{
    size_t *steps = (size_t *)calloc(MAX_STEPS, sizeof(size_t));
    if(NULL != steps)
    {
        steps[*d - 1] = 1;
        for(; steps[*d - 1] * 3 < sz; (*d)++)
        {
            if((*d)%2 == 0) {
                steps[*d] = 9 * (1 << *d) + 9 * (1 << ((*d) / 2)) + 1;
            }
            else
                steps[*d] = 8 * (1 << *d) - 6 * (1 << ((*d + 1) / 2)) + 1;
        }
        (*d)--;
    }
    return steps;
}

void shell_sort(int *arr, size_t sz, int threads)
{
    size_t d = 1;
    size_t *steps = sedgewick_steps(sz, &d); //mallocing memory
    
    if(steps == NULL) {
        return;
    }

    #pragma omp parallel shared(arr, sz, steps, d) default(none) num_threads(threads)
    {
        for (size_t i = 0; i < d; ++i)
        {
            size_t step = steps[d - i - 1];
            #pragma omp for
            for(size_t j = 0; j < step; ++j) {
                insertion_sort(arr, j, sz, step);
            }
        }
    } //#pragma omp parallel

    free(steps); //deallocing memory
}
