#include <iostream>
#include <vector>
#include <random>
#include <chrono>

// Merge two sorted subarrays into one sorted array
std::vector<int> merge(std::vector<int>& leftArr, std::vector<int>& rightArr) {
    std::vector<int> mergedArr;
    int leftSize = leftArr.size();
    int rightSize = rightArr.size();
    int i = 0, j = 0;

    while (i < leftSize && j < rightSize) {
        if (leftArr[i] <= rightArr[j]) {
            mergedArr.push_back(leftArr[i]);
            i++;
        } else {
            mergedArr.push_back(rightArr[j]);
            j++;
        }
    }

    while (i < leftSize) {
        mergedArr.push_back(leftArr[i]);
        i++;
    }

    while (j < rightSize) {
        mergedArr.push_back(rightArr[j]);
        j++;
    }

    return mergedArr;
}

// Recursive function to perform merge sort on the array
std::vector<int> mergeSort(std::vector<int>& arr) {
    int size = arr.size();

    if (size <= 1)
        return arr;

    int middle = size / 2;
    std::vector<int> leftArr(arr.begin(), arr.begin() + middle);
    std::vector<int> rightArr(arr.begin() + middle, arr.end());

    leftArr = mergeSort(leftArr);
    rightArr = mergeSort(rightArr);

    return merge(leftArr, rightArr);
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
    std::uniform_int_distribution<int> dis(1, 100);

    std::vector<int> arr;
    for (int i = 0; i < 10; i++)
        arr.push_back(dis(gen));

    std::cout << "Input array: ";
    printArray(arr);

    auto start = std::chrono::high_resolution_clock::now();

    arr = mergeSort(arr);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Sorted array: ";
    printArray(arr);

    std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;

    return 0;
}
