#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <omp.h>

// Function to generate a random matrix of size n x n
std::vector<std::vector<int>> generateRandomMatrix(int n) {
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
    std::default_random_engine generator(time(0));
    std::uniform_int_distribution<int> distribution(1, 10);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = distribution(generator);
        }
    }

    return matrix;
}

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
    // Create input matrices A and B as random 2x2 matrices
    std::vector<std::vector<int>> A = generateRandomMatrix(2);
    std::vector<std::vector<int>> B = generateRandomMatrix(2);
    
    // Perform matrix multiplication
    std::vector<std::vector<int>> result = matrixMultiplication(A, B);
    
    // Print the matrices
    std::cout << "Matrix A:" << std::endl;
    for (const auto& row : A) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    
    std::cout << "Matrix B:" << std::endl;
    for (const auto& row : B) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    
    // Print the result
    std::cout << "Result:" << std::endl;
    for (const auto& row : result) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
