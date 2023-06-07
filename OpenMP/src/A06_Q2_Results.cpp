#include <iostream>
#include <vector>

double calculateSpeedUp(double serialTime, double parallelTime) {
    return serialTime / parallelTime;
}

double calculateEfficiency(double serialTime, double parallelTime, int numThreads) {
    double speedUp = calculateSpeedUp(serialTime, parallelTime);
    return speedUp / numThreads;
}

int main() {
    std::vector<double> serialTimes = {375.0, 3149.0, 11724.0, 26368.0};

    std::vector<double> parallelTimes_2 = {195.0, 1567.0, 5570.0, 13276.0};
    std::vector<double> parallelTimes_4 = {106.0, 787.0, 2747.0, 6460.0};
    std::vector<double> parallelTimes_8 = {125.0, 516.0, 1614.0, 3576.0};

    std::vector<int> matrixSizes = {250, 500, 750, 1000};

    int numThreads = 2;

    for (int i = 0; i < matrixSizes.size(); i++) {
        int matrixSize = matrixSizes[i];
        double serialTime = serialTimes[i];
        double parallelTime;

        if (numThreads == 2)
            parallelTime = parallelTimes_2[i];
        else if (numThreads == 4)
            parallelTime = parallelTimes_4[i];
        else if (numThreads == 8)
            parallelTime = parallelTimes_8[i];
        else
            continue;

        double speedUp = calculateSpeedUp(serialTime, parallelTime);
        double efficiency = calculateEfficiency(serialTime, parallelTime, numThreads);

        std::cout << "Matrix Size: " << matrixSize << "x" << matrixSize << ", Thread Count: " << numThreads << std::endl;
        std::cout << "Speed-Up: " << speedUp << std::endl;
        std::cout << "Efficiency: " << efficiency << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
