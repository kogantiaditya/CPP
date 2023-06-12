#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

void merge(vector<int> &array, int leftsidearray, int middlepartofthearray, int rightsidearray)
{
    int a = leftsidearray, b = middlepartofthearray + 1, c = 0;
    vector<int> temp(rightsidearray - leftsidearray + 1);

    while (a <= middlepartofthearray && b <= rightsidearray)
    {
        if (array[a] <= array[b])
            temp[c++] = array[a++];
        else
            temp[c++] = array[b++];
    }

    while (a <= middlepartofthearray)
        temp[c++] = array[a++];

    while (b <= rightsidearray)
        temp[c++] = array[b++];

    for (a = leftsidearray, c = 0; a <= rightsidearray; a++, c++)
        array[a] = temp[c];
}

void mergeSort(vector<int> &array, int leftsidearray, int rightsidearray)
{
    if (leftsidearray >= rightsidearray)
        return;

    int middlepartofthearray = (leftsidearray + rightsidearray) / 2;

#pragma omp parallel
    {
#pragma omp single nowait
        {
#pragma omp task
            mergeSort(array, leftsidearray, middlepartofthearray);
        }

#pragma omp single nowait
        {
#pragma omp task
            mergeSort(array, middlepartofthearray + 1, rightsidearray);
        }
    }

    merge(array, leftsidearray, middlepartofthearray, rightsidearray);
}

int main()
{
    int n;
    cout << "Enter the value of n: ";
    cin >> n;

    vector<int> array(n);
    srand(time(0));

    for (int a = 0; a < n; a++)
        array[a] = rand();

    double start_time, end_time;
    int num_threads[] = {1, 2, 4, 8};
    int num_tests = sizeof(num_threads) / sizeof(num_threads[0]);

    for (int a = 0; a < num_tests; a++)
    {
        int threads = num_threads[a];
        omp_set_num_threads(threads);

        start_time = omp_get_wtime();
        mergeSort(array, 0, n - 1);
        end_time = omp_get_wtime();

        cout << "Threads: " << threads << ", Time: " << end_time - start_time << " seconds" << endl;
    }

    return 0;
}
