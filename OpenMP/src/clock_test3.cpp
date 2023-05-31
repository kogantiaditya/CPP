#include <iostream> #include <unistd.h>

#include <ctime>

#include <chrono>

using namespace std;
#include <unistd.h>
int main()

{

    auto begin = chrono::steady_clock::now(); // auto begin = chrono::high_resolution_clock::now(); cout << "1" << endl;

    sleep(5);

    cout << "2" << endl;

    auto end = chrono::steady_clock::now();

    // auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed_seconds = end - begin;
    cout << "Elapsed Time = " << elapsed_seconds.count() << "s" << endl;

    return 0;
}