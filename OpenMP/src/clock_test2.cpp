#include <iostream> #include <unistd.h>
#include <ctime>
#include <unistd.h>
using namespace std;

int main()
{
    clock_t begin = clock();
    cout << "1" << endl;
    sleep(5);
    cout << "2" << endl;
    clock_t end = clock();
    double elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Elapsed Time = " << elapsed_seconds << "s" << endl;
    return 0;
}