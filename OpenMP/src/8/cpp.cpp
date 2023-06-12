#include <iostream>
#include <chrono>

void Pi(int num_steps)
{
    double begin, end, elapsed, pi, step, x, sum;
    int i;
    begin = clock();
    step = 1.0 / static_cast<double>(num_steps);

    sum = 0;

    for (i = 0; i < num_steps; i++)
    {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }

    pi = step * sum;

    end = clock();

    elapsed = (end - begin) / static_cast<double>(CLOCKS_PER_SEC);
    std::cout << "C++ lang based:" << std::endl;
    std::cout << "Pi with " << num_steps << " steps is " << pi << " in " << elapsed << " secs" << std::endl;
}

int main()
{
    Pi(100000000);
    return 0;
}
