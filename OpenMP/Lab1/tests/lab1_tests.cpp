//
// Created by Kether on 02.10.2024.
//
#define CATCH_CONFIG_MAIN

#include "Catch/Catch2.hpp"
#include "../src/max.c"
#include "../src/randomaizer.c"
#include <cstdlib>
#include <ctime>

TEST_CASE("Lab1", "max function test")
{
    srand(time(NULL));
    const int max_size = 1000000UL;
    const size_t border = 10000;
    int *arr = create_array(max_size * sizeof(int));

    SECTION("Sequence")
    {
        for(size_t i = 0; i < border; ++i)
        {
            int size = rand() % max_size;
            REQUIRE(max(arr, size, 1) == max_check(arr, size));
        }
    }

    SECTION("Parallel")
    {
        for(size_t i = 0; i < border; ++i)
        {
            int size = rand() % max_size;
            REQUIRE(max(arr, size, 6) == max_check(arr, size));
        }
    }

    free_array(arr);
}