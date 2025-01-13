//
// Created by Kether on 02.11.2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>


static char *get_sched_kind(omp_sched_t kind)
{
    char *kind_table[] = {"static",
                          "dynamic",
                          "guided",
                          "auto",
                          "implementation defined"};

    size_t kind_table_size = sizeof(kind_table)/sizeof(kind_table[0]);
    size_t k = ((size_t)kind > kind_table_size) ? kind_table_size : kind;
    return kind_table[k - 1];
}

static void check_schedule(void)
{
    omp_sched_t kind;
    int chunk;
    omp_get_schedule(&kind, &chunk);

    printf("Schedule kind is %s and chunk is %d\n", get_sched_kind(kind), chunk);
}

static void check_nested(void)
{
    printf("Nested parallelism is %s\n", (omp_get_nested() == true) ? "on" : "off");
    printf("Max active levels is %d\n", omp_get_max_active_levels());
}

static void check_timer(void)
{
    printf("Timer precision is %lf\n", omp_get_wtick());
}

static void check_dynamic(void)
{
    printf("The dynamic regulation is %s\n", (omp_get_dynamic() == true) ? "on" : "off");
}


static void check_threads(void)
{
    printf("Number of processors is %d\n", omp_get_num_procs());
    printf("Number of max threads is %d\n", omp_get_max_threads());
}

static void check_version(void)
{
    char *version = NULL;
    switch(_OPENMP)
    {
        case 199810:
            version = "1.0";
            break;
        case 200203:
            version = "2.0";
            break;
        case 200505:
            version = "2.5";
            break;
        case 200805:
            version = "3.0";
            break;
        case 201107:
            version = "3.1";
            break;
        case 201307:
            version = "4.0";
            break;
        case 201511:
            version = "4.5";
            break;
        case 201811:
            version = "5.0";
            break;
        case 202011:
            version = "5.1";
            break;
        case 202111:
            version = "5.2";
            break;
        default:
            version = "unknown";
    }
    printf("OpenMP version is %s\n", version);
}

static void d_check_func(void (*check_func)(void))
{
    printf("\n");
    check_func();
    printf("\n");
}

void check_omp(void)
{
    printf("OpenMP environment\n");
    printf("#############################\n");

    void (*funcs[])(void) = {check_version,
                             check_threads,
                             check_dynamic,
                             check_timer,
                             check_nested,
                             check_schedule};

    size_t funcs_size = sizeof(funcs)/sizeof(funcs[0]);

    for(size_t i = 0; i < funcs_size; ++i) {
        d_check_func(funcs[i]);
    }

    printf("#############################\n");
    printf("\n");
}