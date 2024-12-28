//
// Created by Asus on 20.12.2024.
//
#include <stdlib.h>

static int cmp(const void *x, const void *y) {
    int _x = *(int *)x;
    int _y = *(int *)y;
    return (_x < _y) - (_x > _y);
}

void rand_array(int **array, int size)
{
    for(int i = 0; i < size; i++)
        (*array)[i] = rand();

    qsort(*array, size, sizeof(int), cmp);
}