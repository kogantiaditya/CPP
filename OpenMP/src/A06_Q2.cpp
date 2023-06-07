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
    // Get matrix size from the user
    int matrixSize;
    std::cout << "Enter the size of the square matrix: ";
    std::cin >> matrixSize;
    
    // Create input matrices A and B
    std::cout << "Enter the elements of matrix A (" << matrixSize << "x" << matrixSize << "):" << std::endl;
    std::vector<std::vector<int>> A(matrixSize, std::vector<int>(matrixSize));
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            std::cin >> A[i][j];
        }
    }
    
    std::cout << "Enter the elements of matrix B (" << matrixSize << "x" << matrixSize << "):" << std::endl;
    std::vector<std::vector<int>> B(matrixSize, std::vector<int>(matrixSize));
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            std::cin >> B[i][j];
        }
    }
    
    // Get chunk size from the user
    int chunkSize;
    std::cout << "Enter the chunk size: ";
    std::cin >> chunkSize;
    
    // Get number of threads from the user
    int numThreads;
    std::cout << "Enter the number of threads: ";
    std::cin >> numThreads;
    
    // Get the value of P from the user
    int P;
    std::cout << "Enter the value of P: ";
    std::cin >> P;
    
    // Set the number of threads
    omp_set_num_threads(numThreads);
    
    // Perform matrix multiplication and measure the execution time
    auto startTime = std::chrono::steady_clock::now();
    std::vector<std::vector<int>> result = matrixMultiplication(A, B);
    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    
    // Print the result and execution time
    std::cout << "Chunk Size: " << chunkSize << ", Thread Count: " << numThreads << std::endl;
    std::cout << "Result:" << std::endl;
    for (const auto& row : result) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Execution Time: " << duration << " ms" << std::endl;
    
    // Calculate speed-up and efficiency
    double serialTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    double speedup = serialTime / duration;
    double efficiency = speedup / numThreads;
    
    std::cout << "Speed-Up: " << speedup << std::endl;
    std::cout << "Efficiency: " << efficiency << std::endl;
    
    return 0;
}
