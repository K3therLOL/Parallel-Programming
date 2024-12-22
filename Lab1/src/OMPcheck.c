//
// Created by Asus on 19.12.2024.
//
#include <omp.h>
#include <stdio.h>

void check_omp_version(void)
{
#ifdef _OPENMP
    printf("=========\nOpenMP version: %d\n=========\n", _OPENMP);
    printf("\n");
#else
#error Compiler doesnt support OpenMP!
#endif
}