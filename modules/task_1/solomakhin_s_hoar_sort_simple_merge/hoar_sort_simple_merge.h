// Copyright 2021 Solomakhin Sergey
#ifndef MODULES_TASK_1_SOLOMAKHIN_S_HOAR_SORT_SIMPLE_MERGE_HOAR_SORT_SIMPLE_MERGE_H_
#define MODULES_TASK_1_SOLOMAKHIN_S_HOAR_SORT_SIMPLE_MERGE_HOAR_SORT_SIMPLE_MERGE_H_

#include <vector>

std::vector<double> random_gen(int size);
std::vector<double> hoar_sort(int left, int right, std::vector <double>& arr);
//std::vector<int> hoar_sort(std::vector<int>* arr, int first, int last);
std::vector<double> merge(const std::vector<double>& a, const std::vector<double>& b);

#endif  // MODULES_TASK_1_SOLOMAKHIN_S_HOAR_SORT_SIMPLE_MERGE_HOAR_SORT_SIMPLE_MERGE_H_
