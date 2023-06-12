#include <iostream>
#include <chrono>
#include <omp.h>

void Pi(int num_steps)
{
    double begin, end, elapsed, pi, step, x, sum;
    int i;

    begin = omp_get_wtime();
    step = 1.0 / static_cast<double>(num_steps);
    sum = 0;

    #pragma omp parallel for private(x) reduction(+:sum)
    for (i = 0; i < num_steps; i++)
    {
        x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    pi = step * sum;
    end = omp_get_wtime();

    elapsed = end - begin;
    std::cout << "c++ but with parallel processing" << std::endl;
    std::cout << "Pi with " << num_steps << " steps is " << pi << " in " << elapsed << " secs" << std::endl;
}

int main()
{
    Pi(100000000);
    return 0;
}
