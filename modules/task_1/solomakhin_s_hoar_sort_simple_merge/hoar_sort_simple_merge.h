// Copyright 2021 Solomakhin Sergey
#ifndef MODULES_TASK_1_SOLOMAKHIN_S_HOAR_SORT_SIMPLE_MERGE_HOAR_SORT_SIMPLE_MERGE_H_
#define MODULES_TASK_1_SOLOMAKHIN_S_HOAR_SORT_SIMPLE_MERGE_HOAR_SORT_SIMPLE_MERGE_H_

#include <vector>
	
std::vector<int> random_gen(int size);
std::vector<int> hoar_sort(const std::vector<int>& arr, int first, int last);
std::vector<int> merge(const std::vector<int>& a, const std::vector<int>& b);


#endif  // MODULES_TASK_1_SOLOMAKHIN_S_HOAR_SORT_SIMPLE_MERGE_HOAR_SORT_SIMPLE_MERGE_H_
