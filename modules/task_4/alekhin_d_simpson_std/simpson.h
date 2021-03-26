// Copyright 2021 Alekhin Denis
#ifndef MODULES_TASK_4_ALEKHIN_D_SIMPSON_STD_SIMPSON_H_
#define MODULES_TASK_4_ALEKHIN_D_SIMPSON_STD_SIMPSON_H_

#include <utility>
#include <vector>
#include <functional>

double simpsonMethod(
  // Each element of vector contains scope of integration for one dimension.
  // That means, that scope.size() equal to a count of dimentions
  std::vector<std::pair<double, double>> scope,
  std::function<double(std::vector<double>)> func,  // multidimentional function
  int precision  // count of integration intervals
);

#endif  // MODULES_TASK_4_ALEKHIN_D_SIMPSON_STD_SIMPSON_H_

double simpsonMethodSTD(std::vector<std::pair<double, double>> scope,
  std::function<double(std::vector<double>)> func,
  int precision
);
