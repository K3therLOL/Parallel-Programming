//
// Created by Kether on 05.10.2024.
//

#include <iomanip>

#include "../src/randomaizer.cpp"
#include "../src/search.cpp"

template <typename T = int>
double time_search(const std::vector<T> &v, T target, int threads)
{
    double beg, end;
    beg = omp_get_wtime();
    linear_search(v, target, threads);
    end = omp_get_wtime();

    return end - beg;
}

#define OVERPROC 2

void time_algorithm(int test_it = 10)
{
    const size_t size = 50000000ULL;
    int procs = omp_get_num_procs() + OVERPROC;

    for (int proc = 1; proc <= procs; ++proc)
    {
        double res = 0.0;
        for(int i = 0; i < test_it; ++i)
        {
            std::vector<int> v = rand_vector(size, i, i + 1);
            res += time_search(v, i, proc);
        }
        res  /= static_cast<double>(test_it);
        std::cout << "<" << proc << " threads>" << " -- "  << res << " sec\n";
    }
}
