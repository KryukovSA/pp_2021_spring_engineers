// Copyright 2021 Solomakhin Sergey
#ifndef MODULES_TASK_1_SOLOMAKHIN_S_HOAR_SORT_HOAR_SORT_H_
#define MODULES_TASK_1_SOLOMAKHIN_S_HOAR_SORT_HOAR_SORT_H_

#include <vector>
	
std::vector<int> random_gen(int size);
std::vector<int> hoar_sort(std::vector<int>& arr, int first, int last);
std::vector<int> merge(std::vector<int>& a, std::vector<int>& b);


#endif MODULES_TASK_1_SOLOMAKHIN_S_HOAR_SORT_HOAR_SORT_H_