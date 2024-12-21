//
// Created by Kether on 30.09.2024.
//
#include <stdlib.h>

int *rand_array(int *arr, size_t size, int random_seed)
{
    srand(random_seed);
    for(size_t i = 0; i < size; ++i)
        arr[i] = rand();
    return arr;
}