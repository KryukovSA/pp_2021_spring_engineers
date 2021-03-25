// Copyright 2021 Khismatulina Karina
#ifndef MODULES_TASK_1_KHISMATULINA_K_GRADIENT_SEQ_H_
#define MODULES_TASK_1_KHISMATULINA_K_GRADIENT_SEQ_H_
#include <vector>

std::vector<double> getRandomVector(int size);
std::vector<double> getRandomMatrix(int size);
double multVV(std::vector<double> A, std::vector<double> B);
std::vector<double> multMV(std::vector<double> m, std::vector<double> v);
std::vector<double> gradientSeq(const std::vector<double>& matrix, const std::vector<double>& vector, int size);
#endif  // MODULES_TASK_1_KHISMATULINA_K_GRADIENT_SEQ_H_
