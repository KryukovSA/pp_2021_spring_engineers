// Copyright 2021 Frolova Olga
#ifndef MODULES_TASK_1_FROLOVA_O_RADIX_SORT_BATCHER_MERGE_RADIX_SORT_BATCHER_MERGE_H_
#define MODULES_TASK_1_FROLOVA_O_RADIX_SORT_BATCHER_MERGE_RADIX_SORT_BATCHER_MERGE_H_

#include <vector>

std::vector<double> getRandomVector(int size);
std::vector<double> radixSortPos(std::vector<double> vec, int radix);
std::vector<double> checkVector(std::vector<double> vec);
double maxVal(std::vector<double> vec);
int countRadix(double num);
int countNegRadix(double num);
int getRemainder(double num);
std::vector<double> radixSortNeg(std::vector<double> vec, int radix);
std::vector<double> radixSort(std::vector<double> vec);


#endif  // MODULES_TASK_1_FROLOVA_O_RADIX_SORT_BATCHER_MERGE_RADIX_SORT_BATCHER_MERGE_H_
