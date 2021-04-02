// Copyright 2021 Bulychev Andrey
#ifndef MODULES_TASK_1_BULYCHEV_A_SHELL_SORT_SIMPLE_SHELL_SORT_SIMPLE_H_
#define MODULES_TASK_1_BULYCHEV_A_SHELL_SORT_SIMPLE_SHELL_SORT_SIMPLE_H_

#include <vector>


std::vector<double> getRandomVector(int size);
std::vector<double> Shell_sort(const std::vector<double>& vec);
std::vector<double> Merge(const std::vector<double>& vec1, const std::vector<double>& vec2);


#endif  // MODULES_TASK_1_BULYCHEV_A_SHELL_SORT_SIMPLE_SHELL_SORT_SIMPLE_H_
