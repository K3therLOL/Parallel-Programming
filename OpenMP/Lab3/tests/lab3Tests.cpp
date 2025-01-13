//
// Created by Kether on 17.10.2024.
//

#define CATCH_CONFIG_MAIN
#include "Catch/Catch2.h"
#include <cstdlib>
#include <omp.h>

#include "src/isSorted.cpp"
#include "../src/shellSort.c"
#include "../src/randomaizer.c"

TEST_CASE("Lab3", "shell sort")
{
    SECTION("Sequence", "Known")
    {
        int arr[] = {89, -19, 0, 233, 44, 5, -97, 110, 300, 1000, 32, -97};
        int one[] = {-907};
        size_t sz = sizeof(arr)/sizeof(int);
        REQUIRE(is_sorted(arr, sz) == false);
        shell_sort(arr, sz, 1);
        REQUIRE(is_sorted(arr, sz) == true);
        REQUIRE(is_sorted(one, 1) == true);
    }

    SECTION("Sequence", "Random") {
        const size_t sz = 1000000ULL;
        int *arr = (int *)malloc(sz * sizeof(int));
        shell_sort(arr, sz, 1);
        REQUIRE(is_sorted(arr, sz) == true);
        free(arr);
    }

    SECTION("Parallel", "Known") {
        int arr[] = {99, -89, 7, -1000, 567, 48, 388, -10, 56, -89, 10001, 23, -10, 890, 2000, 34, 1};
        size_t sz = sizeof(arr)/sizeof(int);
        for(int rs = 1; rs <= 3; ++rs)
            for(int proc = 1; proc <= omp_get_num_procs(); ++proc) {
                shell_sort(arr, sz, proc);
                REQUIRE(arr[0] == -1000);
                REQUIRE(arr[sz-1] == 10001);
                REQUIRE(is_sorted(arr, sz) == true);
            }
    }

    SECTION("Parallel", "Random")
    {
        const size_t sz = 100000ULL;
        int *arr = (int *)malloc(sz * sizeof(int));

        for(int rs = 1; rs <= 3; ++rs)
            for(int proc = 1; proc <= omp_get_num_procs(); ++proc) {
                arr = rand_array(arr, sz, rs);
                shell_sort(arr, sz, proc);
                REQUIRE(is_sorted(arr, sz) == true);
            }
        free(arr);
    }
}