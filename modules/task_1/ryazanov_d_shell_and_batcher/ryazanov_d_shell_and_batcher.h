// Copyright 2021 Dmitry Ryazanov
#ifndef MODULES_TASK_1_RYAZANOV_D_SHELL_AND_BATCHER_RYAZANOV_D_SHELL_AND_BATCHER_H_
#define MODULES_TASK_1_RYAZANOV_D_SHELL_AND_BATCHER_RYAZANOV_D_SHELL_AND_BATCHER_H_

#include <vector>

std::vector<int> getRandomVector(int sz);
std::vector<int> SortShell(const std::vector<int>& vec);
void print(std::vector<int> const& a);
std::vector<int> sh(const std::vector<int>& vec, int l, int r);
std::vector<int> uns(const std::vector<int>& vec, int l, int r);
std::vector<int> BatcherSort(const std::vector<int>& vec);

#endif  // MODULES_TASK_1_RYAZANOV_D_SHELL_AND_BATCHER_RYAZANOV_D_SHELL_AND_BATCHER_H_
