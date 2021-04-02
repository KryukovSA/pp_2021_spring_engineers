// Copyright 2021 Vizgalov Anton

#ifndef MODULES_TASK_1_VIZGALOV_A_HOARE_SORT_SIMPLE_MERGE_HOARE_SORT_SIMPLE_MERGE_H_
#define MODULES_TASK_1_VIZGALOV_A_HOARE_SORT_SIMPLE_MERGE_HOARE_SORT_SIMPLE_MERGE_H_

#include <vector>

int partition(std::vector<int>* vec, int low, int high);
void hoareSort(std::vector<int>* vec, int low, int high);
void merge(std::vector<int>* vec, int left, int mid, int right);

void runHoareSort(std::vector<int>* vec);

std::vector<int> getRandomVector(int size, int type = 0);

#endif  // MODULES_TASK_1_VIZGALOV_A_HOARE_SORT_SIMPLE_MERGE_HOARE_SORT_SIMPLE_MERGE_H_
