//
// Created by Asus on 20.12.2024.
//
#include <stdlib.h>

void rand_array(int **array, int size)
{
    for(int i = 0; i < size; i++)
        (*array)[i] = rand();
}