#include <iostream>
#include <vector>

double calculateSpeedup(double serialTime, double parallelTime) {
    return serialTime / parallelTime;
}

double calculateEfficiency(double speedup, int numThreads) {
    return speedup / numThreads;
}

int main() {
    double serialTimes[] = {125, 1045, 4089, 9549};

    double parallelTimes[][3][3] = {
        {
            {68, 70, 86},
            {68, 66, 77},
            {70, 68, 68}
        },
        {
            {567, 567, 647},
            {559, 544, 657},
            {546, 559, 567}
        },
        {
            {1872, 2050, 2247},
            {1874, 1875, 2042},
            {1871, 1885, 1846}
        },
        {
            {4635, 4660, 4655},
            {4703, 4617, 5011},
            {4749, 4606, 4735}
        }
    };

    std::vector<int> matrixSizes = {250, 500, 750, 1000};

    std::cout << "Matrix Size\tSchedule\tChunk Size\tSpeedup\t\tEfficiency" << std::endl;

    for (int i = 0; i < matrixSizes.size(); i++) {
        int matrixSize = matrixSizes[i];

        for (int schedule = 0; schedule < 3; schedule++) {
            for (int chunkSize = 0; chunkSize < 3; chunkSize++) {
                double speedup = calculateSpeedup(serialTimes[i], parallelTimes[i][schedule][chunkSize]);
                double efficiency = calculateEfficiency(speedup, 1);
                std::cout << matrixSize << "\t\t" << schedule << "\t\t" << chunkSize << "\t\t" << speedup << "\t\t" << efficiency << std::endl;
            }
        }

        std::cout << std::endl;
    }

    return 0;
}
