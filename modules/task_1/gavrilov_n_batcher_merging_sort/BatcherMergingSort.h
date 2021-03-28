// Copyright 2021 Gavrilov Nikita
#ifndef MODULES_TASK_1_GAVRILOV_N_BATCHER_MERGING_SORT_BATCHERMERGINGSORT_H_
#define MODULES_TASK_1_GAVRILOV_N_BATCHER_MERGING_SORT_BATCHERMERGINGSORT_H_

#include <stdint.h>
#include <utility>
#include <vector>

int8_t GetDigit(int value, uint8_t digidNum, uint8_t rang);
uint8_t GetNumOfDigits(int value, uint8_t rang);
void ConcatVectors(const std::vector<std::vector<int>>& from, std::vector<int>* dest);
void SortByDigid(std::vector<int>* data, uint8_t digitNum, uint8_t rang = 10);
void SortByNumPlace(std::vector<int>* data, uint8_t rang = 10);

void SplitEvenOdd(const std::vector<int>& from, std::vector<int>* destEven, std::vector<int>* destOdd);
void BatcherMerge(std::vector<int> procsLeft, std::vector<int> procsRight, std::vector<std::pair<int, int>>* comps);
void BatcherSplitNMerge(std::vector<int> procs, std::vector<std::pair<int, int>>* comps);
std::vector<std::pair<int, int>> Batcher(int procCount);

void Sort(std::vector<int>* data, int splitCount);

#endif  // MODULES_TASK_1_GAVRILOV_N_BATCHER_MERGING_SORT_BATCHERMERGINGSORT_H_
