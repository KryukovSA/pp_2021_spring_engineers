// Copyright 2021 Ekaterina Burmistrova
#ifndef MODULES_TASK_1_BOURMISTROVA_E_TR_INT_TRAPEZOID_INTEGRAL_H_
#define MODULES_TASK_1_BOURMISTROVA_E_TR_INT_TRAPEZOID_INTEGRAL_H_

#include <vector>
#include <string>
#include <functional>
#include <utility>

// std::vector<int> getRandomVector(int  sz);
double SolveSequential(const std::vector<std::pair<int, int>>& bord,
    std::function<double(double, double, double)> f);
// int getSequentialOperations(std::vector<int> vec, const std::string& ops);

#endif  // MODULES_TASK_1_BOURMISTROVA_E_TR_INT_TRAPEZOID_INTEGRAL_H_
