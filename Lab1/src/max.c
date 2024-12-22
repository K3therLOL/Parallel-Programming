//
// Created by Asus on 19.12.2024.
//
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

/* Parallel max function */
int max(int *arr, size_t size, int threads)
{
    int max = arr[0];

    #pragma omp parallel shared(arr, size) num_threads(threads) reduction(max: max) default(none)
    {
        #pragma omp for
        for(size_t i = 0; i < size; ++i)
            max = (arr[i] > max) ? arr[i] : max;
    }
    return max;
}
