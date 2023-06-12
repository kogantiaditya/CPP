#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <omp.h>

using namespace std;

// Merge function to merge two sorted subarrays
void merge(vector<int>& arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    vector<int> L(n1);
    vector<int> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }
}

// Merge sort function
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                mergeSort(arr, left, middle);
            }

            #pragma omp section
            {
                mergeSort(arr, middle + 1, right);
            }
        }

        merge(arr, left, middle, right);
    }
}

int main() {
    int n, numThreads;
    cout << "Enter the array size: ";
    cin >> n;

    cout << "Enter the number of threads: ";
    cin >> numThreads;

    vector<int> arr(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, 1000);

    cout << "Generated array:\n";
    for (int i = 0; i < n; i++) {
        arr[i] = dis(gen);
      //   cout << arr[i] << " ";
    }
    cout << endl;

    omp_set_num_threads(numThreads);

    double start = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        {
            mergeSort(arr, 0, n - 1);
        }
    }
    double end = omp_get_wtime();

   //  cout << "Sorted array:\n";
   //  for (int i = 0; i < n; i++) {
   //      cout << arr[i] << " ";
   //  }
   //  cout << endl;

    cout << "Time taken: " << end - start << " seconds" << endl;

    return 0;
}