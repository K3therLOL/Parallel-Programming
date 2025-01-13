//
// Created by Kether on 04.10.2024.
//
#include <omp.h>
#include <stdexcept>

void omp_cancellation(char **argv)
{
    if(!omp_get_cancellation()) {
        throw std::runtime_error("Cancellations weren't enabled.");
    }
}
