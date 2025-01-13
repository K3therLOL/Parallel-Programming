//
// Created by Asus on 22.12.2024.
//
#define CATCH_CONFIG_MAIN

#include "include/Catch2.h"
#include "include/isSorted.cpp"
#include "../src/randomaizer.c"
#include "../src/shellSort.c"

TEST_CASE("Lab6", "shell sort")
{
    SECTION("Sequence", "Known")
    {
        int arr[] = {89, -19, 0, 233, 44, 5, -97, 110, 300, 1000, 32, -97};
        int one[] = {-907};
        size_t sz = sizeof(arr)/sizeof(int);
        REQUIRE(is_sorted(arr, sz) == false);
        sequence_shell_sort(arr, sz);
        REQUIRE(is_sorted(arr, sz) == true);
        REQUIRE(is_sorted(one, 1) == true);
    }
    SECTION("Sequence", "Random") {
        const size_t sz = 100000000;
        int *arr = (int *)malloc(sz * sizeof(int));
        rand_array(&arr, sz);
        sequence_shell_sort(arr, sz);
        REQUIRE(is_sorted(arr, sz) == true);
        free(arr);
    }
}