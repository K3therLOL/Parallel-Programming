#include "../src/primeNumbers.c"

#include <cstdio>
#include <catch2/catch_test_macros.hpp>

#define BORDER 1299709
#define SIZE   100000

TEST_CASE("Prime numbers are computed", "[primeNumbers]")
{
    int rk;
    MPI_Comm_rank(MPI_COMM_WORLD, &rk);

    FILE *fp = NULL;
    if(rk == 0) {
        fp = fopen("prime_numbers.txt", "r");
    }

    int package_size = 0;
    int *pk = prime_numbers_package(&package_size, 2, BORDER, 1); 
   
    if(rk == 0) {
        
        REQUIRE(package_size == SIZE); 
    
        int check = 0;
        for(int i = 0; i < package_size; ++i) {
            fscanf(fp, "  %*d => %d,", &check);  
            REQUIRE(check == pk[i]);
        }

        fclose(fp);
    }

}
