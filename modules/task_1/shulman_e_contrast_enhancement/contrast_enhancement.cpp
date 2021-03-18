// Copyright 2021 Shulman Egor
#include "../../../modules/task_1/shulman_e_contrast_enhancement/contrast_enhancement.h"
#include <time.h>
#include <random>
#include <vector>
#include <algorithm>

std::vector<int> getRandomMatrix(int n, int m) {
    if (n < 0 || m < 0)
        throw "Rows or columns less than 0";
    std::mt19937 random;
    random.seed(static_cast<unsigned int>(time(0)));
    std::vector<int> matrix(n * m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i * n + j] = random() % 256;
        }
    }
    return matrix;
}

std::vector<int> ContrastEnhancement(const std::vector<int>& matrix) {
    std::vector<int> result(matrix.size());
    int yMax = 0;
    int yMin = 255;
    for (int i = 0; i < static_cast<int>(matrix.size()); i++) {
        yMax = matrix[i] > yMax ? matrix[i] : yMax;
        yMin = matrix[i] < yMin ? matrix[i] : yMin;
    }
    for (int i = 0; i < static_cast<int>(matrix.size()); i++) {
        result[i] = (matrix[i] - yMin) * (255 / (yMax - yMin));
    }
    return result;
}
