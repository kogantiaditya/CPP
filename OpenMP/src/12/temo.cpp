

#include <iostream>

// Matrix size
#define N 1024

// CUDA kernel for matrix multiplication
__global__ void matrixMultiplication(int* A, int* B, int* C)
{
    // Shared memory for storing submatrices of A and B
    __shared__ int subA[N][N];
    __shared__ int subB[N][N];

    // Calculate global thread indices
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    // Temporary variable for storing the result of one element computation
    int sum = 0;

    // Loop over submatrices of A and B
    for (int i = 0; i < N / blockDim.x; ++i)
    {
        // Load submatrix of A into shared memory
        subA[threadIdx.y][threadIdx.x] = A[row * N + i * blockDim.x + threadIdx.x];

        // Load submatrix of B into shared memory
        subB[threadIdx.y][threadIdx.x] = B[(i * blockDim.y + threadIdx.y) * N + col];

        // Wait for all threads to finish loading
        __syncthreads();

        // Compute partial sum
        for (int j = 0; j < blockDim.x; ++j)
            sum += subA[threadIdx.y][j] * subB[j][threadIdx.x];

        // Wait for all threads to finish computation before loading new submatrices
        __syncthreads();
    }

    // Store the final result in matrix C
    C[row * N + col] = sum;
}

// Function for matrix multiplication on CPU (for result comparison)
void matrixMultiplicationCPU(int* A, int* B, int* C)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            int sum = 0;
            for (int k = 0; k < N; ++k)
            {
                sum += A[i * N + k] * B[k * N + j];
            }
            C[i * N + j] = sum;
        }
    }
}

int main()
{
    // Allocate memory for matrices on host
    int* h_A = new int[N * N];
    int* h_B = new int[N * N];
    int* h_C = new int[N * N];
    int* h_C_CPU = new int[N * N];  // For result comparison

    // Initialize matrices with random values
    for (int i = 0; i < N * N; ++i)
    {
        h_A[i] = rand() % 100;
        h_B[i] = rand() % 100;
    }

    // Allocate memory for matrices on device
    int* d_A;
    int* d_B;
    int* d_C;
    cudaMalloc(&d_A, N * N * sizeof(int));
    cudaMalloc(&d_B, N * N * sizeof(int));
    cudaMalloc(&d_C, N * N * sizeof(int));

    // Copy matrices from host to device
    cudaMemcpy(d_A, h_A, N * N * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, N * N * sizeof(int), cudaMemcpyHostToDevice);

    // Define block size and grid size
    dim3 blockSize(16, 16);
    dim3 gridSize(N / blockSize.x, N / blockSize.y);

    // Launch CUDA kernel for matrix multiplication
    matrixMultiplication<<<gridSize, blockSize>>>(d_A, d_B, d_C);

    // Copy the result matrix from device to host
    cudaMemcpy(h_C, d_C, N * N * sizeof(int), cudaMemcpyDeviceToHost);

    // Perform matrix multiplication on CPU for result comparison
    matrixMultiplicationCPU(h_A, h_B, h_C_CPU);

    // Compare the results
    bool resultCorrect = true;
    for (int i = 0; i < N * N; ++i)
    {
        if (h_C[i] != h_C_CPU[i])
        {
            resultCorrect = false;
            break;
        }
    }

    if (resultCorrect)
        std::cout << "Matrix multiplication results match!" << std::endl;
    else
        std::cout << "Matrix multiplication results do not match." << std::endl;

    // Free memory
    delete[] h_A;
    delete[] h_B;
    delete[] h_C;
    delete[] h_C_CPU;
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}
