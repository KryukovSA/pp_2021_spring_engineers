// Copyright 2021 Sozinov Alex

#include <random>
#include <vector>
#include <algorithm>
#include "../../../modules/task_1/sozinov_a_hoare_batcher/hoare_batcher.h"

std::vector<double> GetRandomVector(int size) {
  std::vector<double> genVec;
  std::random_device dev;
  std::mt19937 ger(dev());
  std::uniform_real_distribution<> realDist(-100, 100);

  for (int index = 0; index < size; ++index) {
    genVec.push_back(realDist(ger));
  }
  return genVec;
}

void Sort(std::vector<double>* vector, int begin, int end) {
  int first = begin, last = end;
  double mid = (*vector)[begin + (end - begin) / 2];

  do {
    while ((*vector)[first] < mid)
      ++first;
    while ((*vector)[last] > mid)
      --last;

    if (first <= last) {
      if (first < last)
        std::swap((*vector)[first], (*vector)[last]);
      ++first;
      --last;
    }
  } while (first <= last);

  if (first < end)
    Sort(vector, first, end);
  if (begin < last)
    Sort(vector, begin, last);
}

void EvenOddSplit(std::vector<double>* res, const std::vector<double>& left,
                  const std::vector<double>& right, EvenOdd type) {
  size_t leftIndex, rightIndex;
  if (type == EvenOdd::Even) {
    leftIndex = 0;
    rightIndex = 0;
  } else {
    leftIndex = 1;
    rightIndex = 1;
  }

  while ((rightIndex < right.size()) && (leftIndex < left.size())) {
    if (left[leftIndex] <= right[rightIndex]) {
      (*res).push_back(left[leftIndex]);
      leftIndex += 2;
    } else {
      (*res).push_back(right[rightIndex]);
      rightIndex += 2;
    }
  }

  if (leftIndex >= left.size()) {
    for (size_t i = rightIndex; i < right.size(); i += 2) {
      (*res).push_back(right[i]);
    }
  } else {
    for (size_t i = leftIndex; i < left.size(); i += 2) {
      (*res).push_back(left[i]);
    }
  }
}

void BatcherMerge(std::vector<double>* res, const std::vector<double>& left, const std::vector<double>& right) {
  std::vector<double> even, odd;
  even.reserve((left.size() + 1) / 2 + (right.size() + 1) / 2);
  odd.reserve(left.size() / 2 + right.size() / 2);
  EvenOddSplit(&even, left, right, EvenOdd::Even);
  EvenOddSplit(&odd, left, right, EvenOdd::Odd);

  size_t index = 0;
  for (; index < even.size() && index < odd.size(); ++index) {
    (*res).push_back(even[index]);
    (*res).push_back(odd[index]);
  }

  if (index < odd.size())
    (*res).insert((*res).end(), odd.begin() + index, odd.end());
  else if (index < even.size())
    (*res).insert((*res).end(), even.begin() + index, even.end());

  for (size_t i = 0; i < (*res).size() - 1; ++i) {
    if ((*res)[i] > (*res)[i + 1]) {
      std::swap((*res)[i], (*res)[i + 1]);
    }
  }
}
