#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

// Function to perform matrix multiplication
std::vector<std::vector<int>> matrixMultiplication(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int n = A.size();
    std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));
    
    #pragma omp parallel for
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
    // Read matrix size and logical core count
    int matrixSize;
    int logicalCores;
    std::cout << "Enter matrix size: ";
    std::cin >> matrixSize;
    std::cout << "Enter logical core count: ";
    std::cin >> logicalCores;
    
    // Create input matrices A and B with all elements as 1
    std::vector<std::vector<int>> A(matrixSize, std::vector<int>(matrixSize, 1));
    std::vector<std::vector<int>> B(matrixSize, std::vector<int>(matrixSize, 1));
    
    for (int i = 0; i < 4; i++) {
        // Perform matrix multiplication and measure the execution time
        auto startTime = std::chrono::steady_clock::now();
        std::vector<std::vector<int>> result = matrixMultiplication(A, B);
        auto endTime = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        
        // Print the result and execution time
        std::cout << "Matrix Size: " << matrixSize << "x" << matrixSize << ", Logical Cores: " << logicalCores << std::endl;
        std::cout << "Result:" << std::endl;
        for (const auto& row : result) {
            for (int val : row) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "Execution Time: " << duration << " ms" << std::endl;
        std::cout << std::endl;
        
        // Increase matrix size for the next iteration
        matrixSize *= 2;
    }
    
    return 0;
}