// Copyright 2021 Sozinov Alex

#ifndef MODULES_TASK_1_SOZINOV_A_HOARE_BATCHER_HOARE_BATCHER_H_
#define MODULES_TASK_1_SOZINOV_A_HOARE_BATCHER_HOARE_BATCHER_H_

#include <vector>

enum EvenOdd {
  Even,
  Odd
};

std::vector<double> GetRandomVector(int size);
void Sort(std::vector<double>* vector, int begin, int end);
void EvenOddSplit(std::vector<double>* res, const std::vector<double>& left,
                  const std::vector<double>& right, EvenOdd type);
void BatcherMerge(std::vector<double>* res, const std::vector<double>& left, const std::vector<double>& right);

#endif  // MODULES_TASK_1_SOZINOV_A_HOARE_BATCHER_HOARE_BATCHER_H_
