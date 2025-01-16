#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <mpi.h>
#include <sys/sysinfo.h>

#include "../include/primeNumbers.h"

static int resolution(void)
{
    double tick = MPI_Wtick();
    int res = 0;
    if(tick <= DBL_EPSILON) {
        return res;
    }

    while(tick < 1.0) {
        res++;
        tick *= 10;
    }

    return res;
}

#define START 2 
#define END   1200000
#define ROOT  0

static double time_prime_numbers(int *array, MPI_Comm comm, int omp_threads)
{
    int rk;
    MPI_Comm_rank(comm, &rk);

    double res = 0.0;
    if(rk == ROOT) {
        res = MPI_Wtime();
    }

    int size = 0;
    prime_numbers_package(array, &size, START, END, comm, omp_threads);

    if(rk == ROOT) {
        res = MPI_Wtime() - res;
    }

    return res;
}

/*static MPI_Comm create_comm(int n)
{
    MPI_Group group;
    MPI_Comm_group(MPI_COMM_WORLD, &group);

    int ranks[] = {0, 1, 2, 3, 4, 5};
    MPI_Group newgroup;
    MPI_Group_incl(group, n, ranks, &newgroup);

    MPI_Comm newcomm;
    MPI_Comm_create(MPI_COMM_WORLD, newgroup, &newcomm);

    return newcomm;
}*/

#define NUM_IT 10

void time_algorithm(void)
{

    MPI_Comm comm = MPI_COMM_WORLD;
    int sz, rk;
    MPI_Comm_rank(comm, &rk);
    MPI_Comm_size(comm, &sz);

    int *array = NULL;
    if(rk == 0 && (array = (int *)malloc(INT_MAX * sizeof(int))) == NULL) {
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    printf("[%d mpi processes]\n", sz);

    for(int proc = 1; proc <= get_nprocs(); ++proc)
    {
        double res = 0.0;
        for(int i = 1; i <= NUM_IT; ++i) 
        {

            double local_res = time_prime_numbers(array, comm, proc);

            if(rk == ROOT) {
                res += local_res;
            }
        }

        if(rk == ROOT) {
            res /= (double)NUM_IT;
            printf("\t<%d threads> --- %.*lf sec\n", proc, resolution(), res);
        }
    }

    free(array);
}
