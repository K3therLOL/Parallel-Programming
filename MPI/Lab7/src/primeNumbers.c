#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <mpi.h>

static void swap(int *x, int *y)
{
    int t = *x;
    *x = *y;
    *y = t;
}

static int isqrt(int x)
{
    int res;
    
    if(x < 9) {
        res = x >> 1;
        return res;
    } else if(x < UINT_LEAST16_MAX) {
        res = (x / 0x3f + 0x3f) >> 1;
        res = (x / res + res)   >> 1;
        res = (x / res + res)   >> 1;
        return res;
    }

    res = (int)sqrt(x);
    return res; 
}

static bool is_prime(int x, int threads)
{
    bool is_prime_number = true;
    
    int border = isqrt(x);

    #pragma omp parallel shared(x, border) reduction(&&: is_prime_number) num_threads(threads) default(none)
    {
        #pragma omp for
        for(int i = 2; i <= border; ++i)
        {
            if(x % i == 0) {
                is_prime_number = false;
            }
        }
    }

    return is_prime_number;
}

static int *find_prime_numbers(int *size, int start, int count, int threads)
{
    *size = 0;
    
    int *array = (int *)malloc(count * sizeof(int));
    if(array == NULL) {
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    for(int i = start; i < start + count; ++i) { 
        if(is_prime(i, threads) == true) {
            array[*size] = i;
            *size += 1;
        }    
    }

    return array;
}

#define ROOT 0

int *prime_numbers_package(int *array, int *size, int start, int end, MPI_Comm comm, int omp_threads)
{
    int sz, rk;
    MPI_Comm_size(comm, &sz);
    MPI_Comm_rank(comm, &rk);
    
    if(start > end) {
        swap(&start, &end);
    }

    int num_of_elements = end - start + 1;
    
    /* MPI starts */

    int elements_per_process = num_of_elements / sz;

    int data[sz];
    int local_start = start;
    if(rk == ROOT) {
        for(int i = 0; i < sz; ++i) {
            data[i]      = local_start;
            local_start += elements_per_process;
        }
    }

    MPI_Scatter(data, 
                1, 
                MPI_INT,
                &local_start, 
                1,
                MPI_INT,
                ROOT,
                comm); 

    int local_size = 0;
    int *sub_array = find_prime_numbers(&local_size, local_start, elements_per_process, omp_threads);

    int recvcounts[sz], displs[sz];

    MPI_Gather(&local_size,
               1,
               MPI_INT,
               recvcounts,
               1,
               MPI_INT,
               ROOT,
               comm);

    int offset = 0;
    if(rk == ROOT) {
    
        for(int i = 0; i < sz; ++i) {
            displs[i] =  offset;
            offset   += recvcounts[i];
        }
        
        local_size = recvcounts[0];
    }

    MPI_Gatherv(sub_array,
                local_size,
                MPI_INT,
                array,
                recvcounts,
                displs,
                MPI_INT,
                ROOT,
                comm);
    
    if(rk == ROOT) {
        int last_portion = num_of_elements % elements_per_process;
        
        if(last_portion == 0) {
            *size = offset;
            free(sub_array);
            return array;
        }

        int last_start = num_of_elements - last_portion + 1;
        int last_size  = 0;
        omp_threads    = 1;

        int *last_part = find_prime_numbers(&last_size, last_start, last_portion + 1, omp_threads);

        memcpy(array + offset, last_part, last_size * sizeof(int));
        offset += last_size;

        *size = offset;
        free(last_part);
    }

    free(sub_array);
    return array;
}
