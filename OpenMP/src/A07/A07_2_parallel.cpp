#include <iostream>
#include <vector>
#include <chrono>
#include <random>

// Merge two sorted subarrays into one sorted array
void merge(std::vector<int>& arr, int left, int middle, int right) {
    std::vector<int> temp(right - left + 1);
    int i = left, j = middle + 1, k = 0;

    #pragma omp parallel
    {
        #pragma omp for
        for (int p = left; p <= right; p++) {
            if (i <= middle && (j > right || arr[i] <= arr[j]))
                temp[k++] = arr[i++];
            else
                temp[k++] = arr[j++];
        }
    }

    for (int p = 0; p < k; p++)
        arr[left + p] = temp[p];
}

// Recursive function to perform merge sort on the array
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSort(arr, left, middle);

            #pragma omp section
            mergeSort(arr, middle + 1, right);
        }

        merge(arr, left, middle, right);
    }
}

// Utility function to print the array
void printArray(const std::vector<int>& arr) {
    for (int i : arr)
        std::cout << i << " ";
    std::cout << std::endl;
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 100);

    std::vector<int> arr(10);
    for (int i = 0; i < 10; i++) {
        arr[i] = dist(gen);
    }

    std::cout << "Input array: ";
    printArray(arr);

    auto startTime = std::chrono::steady_clock::now();

    mergeSort(arr, 0, arr.size() - 1);

    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

    std::cout << "Sorted array: ";
    printArray(arr);

    std::cout << "Execution time: " << duration << " microseconds" << std::endl;

    return 0;
}
