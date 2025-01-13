//
// Created by Kether on 03.10.2024.
//
#include <iostream>
#include <vector>
#include <random>
#include <omp.h>

/* need to parallel */
template <typename T = int>
std::vector<T> rand_vector(size_t sz,
                           unsigned int random_seed,
                           T start = std::numeric_limits<T>::min())
{
    const T beg = start, end = std::numeric_limits<T>::max();

    std::vector<T> v(sz);

    std::mt19937 generator(random_seed);
    std::uniform_int_distribution<T> dist(beg, end);

    for(size_t i = 0; i < sz; ++i) {
        v[i] = dist(generator);
    }

    return v;
}
