// Copyright 2021 Kochankov Ilya
#ifndef MODULES_TEST_TASKS_TEST_OMP_OPS_OMP_H_
#define MODULES_TEST_TASKS_TEST_OMP_OPS_OMP_H_

#include <vector>


std::vector<double> getRandomVector(int sz);
std::vector<double> shell_sort(const std::vector<double>& vec);
std::vector<double> merge(const std::vector<double>& a, const std::vector<double>& b);


#endif  // MODULES_TEST_TASKS_TEST_OMP_OPS_OMP_H_