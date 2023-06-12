#include <iostream>
#include <vector>
#include <chrono>
#include <random>

void merge(std::vector<int>& array, int leftSideArray, int middlePart, int rightSideArray) {
    std::vector<int> temp(rightSideArray - leftSideArray + 1);
    int i = leftSideArray, j = middlePart + 1, k = 0;

    for (int p = leftSideArray; p <= rightSideArray; p++) {
        if (i <= middlePart && (j > rightSideArray || array[i] <= array[j]))
            temp[k++] = array[i++];
        else
            temp[k++] = array[j++];
    }

    for (int p = 0; p < k; p++)
        array[leftSideArray + p] = temp[p];
}

void mergeSort(std::vector<int>& array, int leftSideArray, int rightSideArray) {
    if (leftSideArray < rightSideArray) {
        int middlePart = leftSideArray + (rightSideArray - leftSideArray) / 2;

        mergeSort(array, leftSideArray, middlePart);
        mergeSort(array, middlePart + 1, rightSideArray);

        merge(array, leftSideArray, middlePart, rightSideArray);
    }
}

void printArray(const std::vector<int>& array) {
    for (int i : array)
        std::cout << i << " ";
    std::cout << std::endl;
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 10000);

    std::vector<int> array(100);
    for (int i = 0; i < 100; i++) {
        array[i] = dist(gen);
    }

    std::cout << "Input array: ";
    // printArray(array);

    auto startTime = std::chrono::steady_clock::now();

    mergeSort(array, 0, array.size() - 1);

    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

    std::cout << "Sorted array: ";
    // printArray(array);

    std::cout << "Execution time: " << duration << " microseconds" << std::endl;

    return 0;
}
