#include "../src/primeNumbers.c"

#include <cstdio>
#include <catch2/catch_test_macros.hpp>

#define BORDER 1299709
#define SIZE   100000

TEST_CASE("Prime numbers are computed", "[primeNumbers]")
{
    
    int rk, sz;
    MPI_Comm_rank(MPI_COMM_WORLD, &rk);
    MPI_Comm_size(MPI_COMM_WORLD, &sz);

    FILE *fp = NULL;
    if(rk == 0) {
        fp = fopen("prime_numbers.txt", "r");
    }

    int *array = NULL;
    if(rk == 0) {
        array = (int *)malloc(BORDER * sizeof(int));
    }

    double r;

    for(int i = 1; i <= sz; ++i)
    {
        if(rk == 0) {
            r = MPI_Wtime();
        }

        int package_size = 0;
        prime_numbers_package(array, &package_size, 2, BORDER, MPI_COMM_WORLD, i); 

        if(rk == 0) {
            r = MPI_Wtime() - r;
            printf("%d processor time = %f sec\n", i, r);
           
           REQUIRE(package_size == SIZE); 

            int check = 0;
            for(int j = 0; j < package_size; ++j) {
                fscanf(fp, "  %*d => %d,", &check);  
                REQUIRE(check == array[j]);
            }

            fseek(fp, 0, SEEK_SET);
        
        }

    }
    
    if(rk == 0) {
        free(array);
        fclose(fp);
    }
}
