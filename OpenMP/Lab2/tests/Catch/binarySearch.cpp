//
// Created by Kether on 11.10.2024.
//
#include <vector>
#include <cassert>
#include <algorithm>

template <typename T = int>
size_t binary_search(std::vector<T> v, T target)
{

    assert(std::is_sorted(v.cbegin(), v.cend()));

    size_t index = std::numeric_limits<T>::max();

    size_t l = 0, r = v.size(), m = 0;

    while (l != r)
    {
        m = l + (r - l) / 2;

        if (target < v[m]) {
            r = m;
        }

        else if (v[m] < target) {
            l = m + 1;
        }

        else {
            index = m;
            break;
        }
    }

    return index;
}