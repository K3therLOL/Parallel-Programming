//
// Created by Kether on 19.10.2024.
//
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
    int arg = *(const int *)a;
    int brg = *(const int *)b;

    return (arg < brg) - (arg > brg);
}

int *rand_array(int *arr, size_t sz, int random_seed)
{
    srand(random_seed);
    #pragma omp parallel shared(arr, sz) default(none)
    {
        #pragma omp for simd
        for(size_t i = 0; i < sz; ++i)
            arr[i] = rand();
    } //#pragma omp parallel

    qsort(arr, sz, sizeof(int), cmp);

    return arr;
}