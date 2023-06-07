#include <iostream>
#include <vector>
#include <omp.h>

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
    std::cout << "Enter 1st matrix (2 rows and 2 numbers each): " << std::endl;
    std::vector<std::vector<int>> A(2, std::vector<int>(2));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            std::cin >> A[i][j];
        }
    }
    
    std::cout << "Enter 2nd matrix (2 rows and 2 numbers each): " << std::endl;
    std::vector<std::vector<int>> B(2, std::vector<int>(2));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            std::cin >> B[i][j];
        }
    }
    
    std::vector<std::vector<int>> result = matrixMultiplication(A, B);
    
    std::cout << "Result:" << std::endl;
    for (const auto& row : result) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
