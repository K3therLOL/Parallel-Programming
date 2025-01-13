#include <stdio.h>
#include <omp.h>
#include <stdbool.h>

void print_square(size_t cols, size_t rows)
{
    omp_lock_t lock;
    omp_init_lock(&lock);
    #pragma omp parallel shared(cols, rows, lock) default(none)
    {
        #pragma omp for
        for(size_t i = 0; i < cols; ++i)
        {
            for(size_t j = 0; j < rows; ++j) {
                printf("#");
            }

            omp_set_lock(&lock);
            printf("\n");
            omp_unset_lock(&lock);
        }
    }
    omp_destroy_lock(&lock);
}

bool lock_example(void)
{
    size_t cols, rows;

    printf("Enter the number of columns and rows:");
    if(scanf("%zu%zu", &cols, &rows) < 2) {
        fprintf(stderr, "Wrong input\n");
        return false;
    }

    print_square(cols, rows);
    return true;
}
