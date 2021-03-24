// Copyright 2021 Maksimov Andrey
#ifndef MODULES_TASK_1_MAKSIMOV_A_MATR_MULTIPLY_MATRIX_MULTIPLY_H_
#define MODULES_TASK_1_MAKSIMOV_A_MATR_MULTIPLY_MATRIX_MULTIPLY_H_
#include <vector>

std::vector<double> generateMatrix(int rows);
std::vector<double> mupltiplyMatrixByMatrix(
    std::vector<double> matr1,
    std::vector<double> matr2,
    int matr1Rows, int matr2Rows);
#endif  // MODULES_TASK_1_MAKSIMOV_A_MATR_MULTIPLY_MATRIX_MULTIPLY_H_
