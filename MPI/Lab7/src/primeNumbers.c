#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
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
    
    int *arr = (int *)malloc(count * sizeof(int));
    if(arr == NULL) {
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    for(int i = start; i < start + count; ++i) { 
        if(is_prime(i, threads) == true) {
            arr[*size] = i;
            *size += 1;
        }    
    }

    return arr;
}

int *prime_numbers_package(int *size, int start, int end, int threads)
{
    int sz, rk;
    MPI_Comm_size(MPI_COMM_WORLD, &sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &rk);
    
    if(start > end) {
        swap(&start, &end);
    }

    int num_of_elements = end - start + 1;
    
    int *array = NULL;
    if(rk == 0 && (array = (int *)malloc(num_of_elements * sizeof(int))) == NULL) {
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    /* MPI starts */

    int elements_per_process = num_of_elements / sz;

    int data[sz];
    int local_start = start;
    for(int i = 0; i < sz; ++i) {
        data[i]      = local_start;
        local_start += elements_per_process;
    }

    MPI_Scatter(data, 
                1, 
                MPI_INT,
                &local_start, 
                1,
                MPI_INT,
                0,
                MPI_COMM_WORLD); 

    int local_size = 0;
    int *sub_array = find_prime_numbers(&local_size, local_start, elements_per_process, threads);

    //MPI_Request request;
    //MPI_Status status;

    MPI_Gather(&local_size,
               1,
               MPI_INT,
               recvcounts,
               1,
               MPI_INT,
               0,
               MPI_COMM_WORLD);

    int offset = 0;
    if(rk == 0) {
    
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
                0,
                MPI_COMM_WORLD);
    
    if(rk == 0) {
        
        int last_portion = num_of_elements % elements_per_process;
        
        if(last_portion == 0) {
            *size = offset;
            free(sub_array);
            return array;
        }

        int last_size = 0;
        int *last_part = find_prime_numbers(&last_size, offset, last_portion, threads);

        memcpy(array + offset, last_part, last_size);
        offset += last_size;

        *size = offset;
        free(last_part);
    }

    free(sub_array);
    return array;
}

/*void print_prime_numbers(int start, int end, int threads)
{
    int rk;
    MPI_Comm_rank(MPI_COMM_WORLD, &rk);

    int size = 0;
    int *array = prime_numbers_package(&size, start, end, threads);
    if(rk == 0) {
        printf("\nPrime numbers:\n");
        for(int i = 0; i < size; ++i)
            printf("%d\n", array[i]);
    }

    free(array);
}*/
