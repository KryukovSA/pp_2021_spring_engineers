// Copyright 2021 Ivanov Yaroslav
#ifndef MODULES_TASK_1_IVANOV_Y_SORT_DOUBLE_SORT_DOUBLE_H_
#define MODULES_TASK_1_IVANOV_Y_SORT_DOUBLE_SORT_DOUBLE_H_

#include <string>
#include <random>
#include <ctime>
#include <algorithm>

double* BubbleForCompare(double* inputNumbers, int size);
double* generateDouble(int n);
void loc_sort(double* inputNumers, int size);
void transit(double* inputNumers, double* loc, int size, int add);
void transit1(double* inputNumers, double* loc, int size, int add);

#endif  // MODULES_TASK_1_IVANOV_Y_SORT_DOUBLE_SORT_DOUBLE_H_
