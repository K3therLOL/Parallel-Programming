//
// Created by Kether on 04.10.2024.
//
#define CATCH_CONFIG_MAIN
#include "Catch/Catch2.h"
#include "Catch/binarySearch.cpp"

#include "../src/randomaizer.cpp"
#include "../src/search.cpp"

TEST_CASE("Rand function")
{
    SECTION("Success")
    {
        std::vector<int> v1  = rand_vector(1000, 10);
        std::vector<int> v2  = rand_vector(1000, 10);
        REQUIRE(v1 == v2);

        std::vector<int> v_1 = rand_vector(2000000, 33, -10);
        std::vector<int> v_2 = rand_vector(2000000, 33, -10);
        REQUIRE(v_1 == v_2);
    }

    SECTION("Sequence failure")
    {
        std::vector<int> v1 = rand_vector(1000, 10, 1);
        std::vector<int> v2 = rand_vector(1000, 11, 1);
        std::vector<int> v3 = rand_vector(999, 11, 1);
        REQUIRE(!(v1 == v2));
        REQUIRE(!(v2 == v3));
    }
}

TEST_CASE("Linear search")
{
    SECTION("Unsorted array", "Rand")
    {
        std::vector<int> v1 = rand_vector(10000ULL, 1);
        for(int i = 1; i <= omp_get_num_procs(); ++i) {
            for(size_t j = 0; j < v1.size(); ++j) {
                REQUIRE(v1[linear_search(v1, v1[j], i)] == v1[j]);
            }
        }
    }

    SECTION("Unsorted array", "Known")
    {
        const size_t not_found = std::numeric_limits<size_t>::max();
        std::vector<int> v1 = {908, 34, 77, 605, 44, 3, -20, 1};
        for(int i = 1; i <= omp_get_num_procs(); ++i) {
            REQUIRE(linear_search(v1, 0, i) == not_found);
        }
        for(int i = 1; i <= omp_get_num_procs(); ++i) {
            REQUIRE(linear_search(v1, -10, i) == not_found);
        }
        for(int i = 1; i <= omp_get_num_procs(); ++i) {
            REQUIRE(linear_search(v1, 1000, i) == not_found);
        }
        for(int i = 1; i <= omp_get_num_procs(); ++i) {
            REQUIRE(linear_search(v1, 908, i) == 0);
        }
        for(int i = 1; i <= omp_get_num_procs(); ++i) {
            REQUIRE(linear_search(v1, 44, i) == 4);
        }
    }

    SECTION("binary search")
    {
        std::vector<int> v = rand_vector(10000ULL, 9);
        std::sort(v.begin(), v.end());
        for(size_t i = 0; i < v.size(); ++i) {
            for(int j = 1; j <= omp_get_num_procs() + 14; ++j) {
                REQUIRE(v[linear_search(v, v[i], j)] == v[binary_search(v, v[i])]);
            }
        }
    }
}


