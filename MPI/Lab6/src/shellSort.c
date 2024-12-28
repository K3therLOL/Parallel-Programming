//
// Created by Asus on 20.12.2024.
//
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <mpi.h>
#include <stdio.h>

static void swap(int *x, int *y)
{
    int t = *x;
    *x = *y;
    *y = t;
}

#define MAX_STEPS 31

static int *sedgewick_steps(int sz, int *d)
{
    int *steps = (int *)calloc(MAX_STEPS, sizeof(int));
    if(NULL != steps)
    {
        steps[*d - 1] = 1;
        for(; steps[*d - 1] * 3 < sz; (*d)++)
        {
            if((*d) % 2 == 0) {
                steps[*d] = 9 * (1 << *d) + 9 * (1 << ((*d) / 2)) + 1;
            }

            else {
                steps[*d] = 8 * (1 << *d) - 6 * (1 << ((*d + 1) / 2)) + 1;
            }
        }
        (*d)--;
    }

    return steps;
}

static bool sequence_shell_sort(int *array, int size)
{
    int d = 1;
    int *steps = sedgewick_steps(size, &d);
    if (steps == NULL) {
        return false;
    }

    for (int i = 0; i < d; ++i)
    {

        int step = steps[d - i - 1];

        for (int j = step; j < size; ++j)
            for (int k = j - step; k >= 0 && array[k] > array[k + step]; k -= step)
                swap(&array[k], &array[k + step]);
    }

    free(steps);
    return true;
}

static int cmp(const void *x, const void *y) {
    int _x = *(int *)x;
    int _y = *(int *)y;
    return (_x > _y) - (_x < _y);
}

bool shell_sort(int *array, int size)
{
    int sz, rk;
    MPI_Comm_size(MPI_COMM_WORLD, &sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &rk);
    MPI_Status status;

    int elements_per_process = size / sz;

    int *sub_array = (int *)malloc(elements_per_process * sizeof(int));
    if (sub_array == NULL) {
        return false;
    }

    MPI_Scatter(array,
                elements_per_process,
                MPI_INT,
                sub_array,
                elements_per_process,
                MPI_INT,
                0,
                MPI_COMM_WORLD);

    sequence_shell_sort(sub_array, elements_per_process);

    int *recvcounts = NULL, *displs = NULL;
    if (rk == 0) {
        recvcounts = (int *)malloc(sz * sizeof(int));
        displs     = (int *)malloc(sz * sizeof(int));
        if (recvcounts == NULL || displs == NULL) {
            return false;
        }

        int i = 0;
        for (; i < sz - 1; ++i) {
            recvcounts[i] = elements_per_process;
            displs[i]     = i * elements_per_process;

        }
        recvcounts[i] = size - i * elements_per_process;
        displs[i]     = i * elements_per_process;
    }

    MPI_Gatherv(sub_array,
                elements_per_process,
                MPI_INT,
                array,
                recvcounts,
                displs,
                MPI_INT,
                0,
                MPI_COMM_WORLD);

    if (rk == 0) {
        sequence_shell_sort(array, size);
    }

    free(recvcounts);
    free(displs);
    free(sub_array);
    return true;
}