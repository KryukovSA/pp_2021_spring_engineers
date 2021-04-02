// Copyright 2021 Baulin Mikhail

#ifndef MODULES_TASK_1_BAULIN_M_RADIX_SORT_SIMPLE_MERGE_RADIX_SORT_H_
#define MODULES_TASK_1_BAULIN_M_RADIX_SORT_SIMPLE_MERGE_RADIX_SORT_H_
#include <vector>

std::vector<double> GetRandomVector(int size);
std::vector<double> CountingSort(std::vector<double> vec1,
                                 std::vector<double> vec2, int byteNum);
std::vector<double> negative_sort(std::vector<double> source, int offset);
std::vector<double> RadixSort(const std::vector<double>& vec);
std::vector<double> Merge(const std::vector<double>& a,
                          const std::vector<double>& b);

#endif  // MODULES_TASK_1_BAULIN_M_RADIX_SORT_SIMPLE_MERGE_RADIX_SORT_H_
