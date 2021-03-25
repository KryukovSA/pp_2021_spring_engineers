// Copyright 2021 Maksimov Andrey
#include <time.h>
#include <random>
#include <vector>
#include "../../modules/task_1/maksimov_a_matr_multiply/matrix_multiply.h"

std::vector<double> generateMatrix(int rows) {
    std::mt19937 gen;
    gen.seed(time(0));

    std::vector<double> matr(rows * rows);
    for (int i = 0; i < rows * rows; i++) {
        matr[i] = static_cast<double>(gen()) / RAND_MAX * 9.0 + 1.0;
    }
    return matr;
}

std::vector<double> mupltiplyMatrixByMatrix(
    std::vector<double> matr1,
    std::vector<double> matr2,
    int matr1Rows, int matr2Rows) {
    if (matr1Rows != matr2Rows)
        throw "matr1Rows != matr2Rows";

    std::vector<double> result(matr1Rows * matr1Rows);
    for (int i = 0; i < matr1Rows; i++) {
        for (int j = 0; j < matr1Rows; j++) {
            result[i * matr1Rows + j] = 0;
            for (int k = 0; k < matr1Rows; k++) {
                result[i * matr1Rows + j]
                    += matr1[i * matr1Rows + k] * matr2[k * matr1Rows + j];
            }
        }
    }
    return result;
}
