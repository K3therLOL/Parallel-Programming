//
// Created by Kether on 19.10.2024.
//
#include <cstddef>
bool is_sorted(int *arr, size_t sz)
{
    for(size_t i = 1; i < sz; ++i)
    {
        if(arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}