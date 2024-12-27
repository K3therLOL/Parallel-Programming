//
// Created by Asus on 20.12.2024.
//
#include <stdlib.h>
#include <stdbool.h>
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

bool sequence_shell_sort(int *array, int size)
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

bool shell_sort(int *array, int size)
{
    int sz, rk;
    MPI_Comm_size(MPI_COMM_WORLD, &sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &rk);
    MPI_Status status;

    //int *sub_array = NULL;
    int elements_per_process = size / sz;

    if (rk == 0) {
        int i;
        for (i = 0; i < sz - 1; ++i) {
            MPI_Send(array + elements_per_process * i,
                     elements_per_process,
                     MPI_INT,
                     i + 1,
                     0,
                     MPI_COMM_WORLD);
        }

        for (i = 0; i < sz - 1; ++i) {
            MPI_Recv(array + elements_per_process * i,
                     elements_per_process,
                     MPI_INT,
                     i + 1,
                     1,
                     MPI_COMM_WORLD,
                     &status);
        }

        int elements_remain = size - i * elements_per_process;
        sequence_shell_sort(array + elements_per_process * i, elements_remain);

    }
    else {

        int *sub_array = (int *)malloc(elements_per_process * sizeof(int));
        if (sub_array == NULL) {
            return false;
        }

        MPI_Recv(sub_array,
                 elements_per_process,
                 MPI_INT,
                 0,
                 MPI_ANY_TAG,
                 MPI_COMM_WORLD,
                 &status);
        printf("Sub array before\n");
        for (int i = 0; i < elements_per_process; ++i)
            printf("%d ", sub_array[i]);
        printf("\n");

        sequence_shell_sort(sub_array, elements_per_process);

        printf("Sub array after\n");
        for (int i = 0; i < elements_per_process; ++i)
            printf("%d ", sub_array[i]);
        printf("\n");

        MPI_Send(sub_array,
                elements_per_process,
                MPI_INT,
                0,
                1,
                MPI_COMM_WORLD);

        free(sub_array);
    }
    return true;
}