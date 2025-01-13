//
// Created by Kether on 02.11.2024.
//

#include <stdlib.h>
#include "../include/checkOMP.h"
#include "../include/lockExample.h"
#include "../include/scheduleExample.h"

int main()
{
    check_omp();

    if(false == lock_example()) {
        return EXIT_FAILURE;
    }

    if(false == schedule_example()) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
