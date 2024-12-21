
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

int cmp(const void *a, const void *b)
{
    int arg = *(const int *)a;
    int brg = *(const int *)b;

    return (arg < brg) - (arg > brg);
}

/* Function for testing */
int max_check(int *arr, size_t size)
{
    assert(size != 0);

    qsort(arr, size, sizeof(int), cmp);
    return arr[0];
}