// Copyright 2021 Boytsov Vladislav
#ifndef MODULES_TASK_1_BOYTSOV_V_MONTE_CARLO_MONTE_CARLO_H_
#define MODULES_TASK_1_BOYTSOV_V_MONTE_CARLO_MONTE_CARLO_H_

#include <vector>
#include <string>

double getSequentialOperations(double(*f)(std::vector<double>), const std::vector<double>& a,
                               const std::vector<double>& b, int n);

#endif  // MODULES_TASK_1_BOYTSOV_V_MONTE_CARLO_MONTE_CARLO_H_
