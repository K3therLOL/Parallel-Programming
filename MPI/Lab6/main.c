#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/timeShellSort.h"

#include "include/shellSort.h"

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);



    int rk;
    MPI_Comm_rank(MPI_COMM_WORLD, &rk);
    printf("rank = %d\n", rk);

    int arr[] = {72, 38, -100, 1234, -1, 33, 102};
    int sz = sizeof(arr) / sizeof(arr[0]);
    if (rk == 0) {
        printf("Before sort\n");
        for (int i = 0; i < sz; ++i)
            printf("%d ", arr[i]);
        printf("\n");
    }

    shell_sort(arr, sz);

    if (rk == 0) {
        printf("After sort\n");
        for (int i = 0; i < sz; ++i)
            printf("%d ", arr[i]);
        printf("\n");
    }

    MPI_Finalize();
}