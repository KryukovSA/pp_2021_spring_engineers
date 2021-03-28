// Copyright 2021 Evseev Alexander
#ifndef MODULES_TASK_1_EVSEEV_A_GAUSS_EVSEEV_A_GAUSS_H_
#define MODULES_TASK_1_EVSEEV_A_GAUSS_EVSEEV_A_GAUSS_H_

#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

using Matrix = std::vector<std::vector<double>>;
Matrix RandMatrix(int hight, int widht);
int clamp(int value, int max, int min);
Matrix GaussKernel(int R, double sigma);
Matrix SeqGauss(Matrix mat, int rows, int cols, int R,
                            double alpha);
void printMatrix(Matrix mat, int hight, int widht);

#endif  // MODULES_TASK_1_EVSEEV_A_GAUSS_EVSEEV_A_GAUSS_H_
