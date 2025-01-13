#include <iostream>

#include "../include/ompCancellation.h"
#include "../include/timeAlgorithm.h"


int main(int argc, char **argv)
{
    try {

        omp_cancellation(argv);
        time_algorithm();

    }catch(std::bad_alloc &ba) {
        
        std::cerr << ba.what() << "\n";
        return EXIT_FAILURE;
    
    }catch(std::exception &ex) {
        
        std::cerr << ex.what() << "\n";
        return EXIT_FAILURE;
    
    }

    return EXIT_SUCCESS;
}
