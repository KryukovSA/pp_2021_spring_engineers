// Copyright 2021 Ivanov Yaroslav
#ifndef MODULES_TASK_1_IVANOV_Y_DOUBLE_SORT_SORT_DOUBLE_H_
#define MODULES_TASK_1_IVANOV_Y_DOUBLE_SORT_SORT_DOUBLE_H_

double* BubbleForCompare(double* inputNumbers, const int size);
double* generateDouble(const int n);
void loc_sort(double* inputNumers, const int size);
void transit(double* inputNumers, double* loc, const int size, int add);
void transit1(double* inputNumers, double* loc, const int size, int add);

#endif  // MODULES_TASK_1_IVANOV_Y_DOUBLE_SORT_SORT_DOUBLE_H_
