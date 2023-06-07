#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

std::vector<std::vector<int>> matrixMultiplication(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int n = A.size();
    std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return result;
}

int main() {
    int numThreads;
    std::cout << "Enter threads: ";
    std::cin >> numThreads;

    std::vector<int> matrixSizes = {250, 500, 750, 1000};

    for (int matrixSize : matrixSizes) {
        std::vector<std::vector<int>> A(matrixSize, std::vector<int>(matrixSize, 1));
        std::vector<std::vector<int>> B(matrixSize, std::vector<int>(matrixSize, 1));

        omp_set_num_threads(numThreads);

        auto startTime = std::chrono::steady_clock::now();
        std::vector<std::vector<int>> result = matrixMultiplication(A, B);
        auto endTime = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

        std::cout << "Matrix Size: " << matrixSize << "x" << matrixSize << ", Thread Count: " << numThreads << std::endl;
        std::cout << "Execution Time: " << duration << " ms" << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
