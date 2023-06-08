#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void merge(vector<int>& array, int leftsidearray, int middlepartofthearray, int rightsidearray)
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

void mergeSort(vector<int>& array, int leftsidearray, int rightsidearray)
{
    if (leftsidearray >= rightsidearray)
        return;

    int middlepartofthearray = (leftsidearray + rightsidearray) / 2;

    mergeSort(array, leftsidearray, middlepartofthearray);
    mergeSort(array, middlepartofthearray + 1, rightsidearray);

    merge(array, leftsidearray, middlepartofthearray, rightsidearray);
}

int main()
{
    int n;
    cout << "n: ";
    cin >> n;

    vector<int> array(n);
    srand(time(0));

    for (int a = 0; a < n; a++)
        array[a] = rand();

    double start_time, end_time;

    start_time = clock();
    mergeSort(array, 0, n - 1);
    end_time = clock();

    cout << "time: " << (end_time - start_time) / CLOCKS_PER_SEC << " sec" << endl;

    return 0;
}
