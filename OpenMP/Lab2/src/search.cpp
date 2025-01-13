//
// Created by Kether on 04.10.2024.
//
#include <limits>
#include <vector>
#include <algorithm>
#include <iostream>

/* parallel linear search */
template <typename T = int>
size_t linear_search(const std::vector<T> &v, T target, int threads)
{
    size_t index = std::numeric_limits<size_t>::max();

    #pragma omp parallel num_threads(threads) shared(v, target, index) default(none)
    {
        #pragma omp for
        for(size_t i = 0; i < v.size(); ++i)
        {
            if(v[i] == target)
            {
                #pragma omp critical
                {
                    index = i;
                }
            #pragma omp cancel for
            }
        #pragma omp cancellation point for
        }
    }
    return index;
}

