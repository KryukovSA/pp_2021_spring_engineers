// Copyright 2021 Khismatulina Karina
#ifndef MODULES_TASK_1_KHISMATULINA_K_SEQ_SEQ_H_
#define MODULES_TASK_1_KHISMATULINA_K_SEQ_SEQ_H_

#include <vector>

std::vector<int> getRandomVector(int size);
std::vector<int> getRandomMatrix(int size);
int vecMult(std::vector<int> A, std::vector<int> B);
std::vector<int> matrixVecMult(std::vector<int> m, std::vector<int> v);
std::vector<int> gradientSeq(const std::vector<int>& matrix, const std::vector<int>& vector, int size);
#endif  // MODULES_TASK_1_KHISMATULINA_K_SEQ_SEQ_H_
