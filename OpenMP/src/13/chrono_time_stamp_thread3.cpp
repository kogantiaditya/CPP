#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>

using namespace std;
typedef unsigned long long int uint64;

void sumEvenNumbers(uint64& start, uint64& end, uint64& even_sum)
{
    for(uint64 i=start; i<=end; i++)
    {
        if ((i & 1) == 0)
            even_sum += i;
    }

}

void sumOddNumbers(uint64& start, uint64& end, uint64& odd_sum)
{
    for(uint64 i=start; i<=end; i++)
    {
        if ((i & 1) == 1)
            odd_sum += i;
    }

}

int main()
{
    auto time_s = chrono::high_resolution_clock::now();

    uint64 start = 0, end = 1000000000;
    uint64 even_sum = 0;
    uint64 odd_sum = 0;

    std::thread t1(sumEvenNumbers, std::ref(start), std::ref(end), std::ref(even_sum));
    std::thread t2(sumOddNumbers, std::ref(start), std::ref(end), std::ref(odd_sum));

    t1.join();
    t2.join();

    cout << "Even Sum = " << even_sum << endl;
    cout << "Odd Sum = " << odd_sum << endl;

    auto time_e = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed_time = time_e - time_s;
    cout << "Elapsed time: " << elapsed_time.count() << "sec\n";

    return 0;
}