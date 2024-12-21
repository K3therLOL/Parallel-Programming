//
// Created by Kether on 02.11.2024.
//

#ifndef CHECKOMP_H
#define CHECKOMP_H

#include <omp.h>

char *get_sched_kind(omp_sched_t kind);

void check_schedule(void);

void check_timer(void);

void check_dynamic(void);

void check_threads(void);

void check_version(void);

void d_check_func(void (*)(void));

void check_omp(void);

#endif //CHECKOMP_H
