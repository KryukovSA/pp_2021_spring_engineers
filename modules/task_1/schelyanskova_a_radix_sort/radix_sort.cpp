// Copyright 2021 Schelyanskova Anastasiia

#include "../../../modules/task_1/schelyanskova_a_radix_sort/radix_sort.h"

#include <math.h>

#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <vector>

std::vector<int> getRandomVector(int sz) {
  std::random_device dev;
  std::mt19937 gen(dev());
  std::vector<int> vect(sz);
  for (int i = 0; i < sz; i++) {
    vect[i] = gen() % 100;
  }
  return vect;
}
int get_max_power(std::vector<int> vect) {
  int max_power = 0;
  int tmp = vect[0];
  int size = vect.size();
  for (int i = 0; i < size; i++) {
    if (tmp < vect[i]) {
      tmp = vect[i];
    }
  }
  if (tmp == 0) {
    return 1;
  }
  while (tmp != 0) {
    tmp = tmp / 10;
    max_power++;
  }
  return max_power;
}

std::vector<int> bubble_sort_vector(std::vector<int> vect) {
  int j = 0;
  int tmp = 0;
  int length = vect.size();
  for (int i = 0; i < length; i++) {
    j = i;
    for (int m = i; m < length; m++) {
      if (vect[j] > vect[m]) {
        j = m;
      }
    }
    tmp = vect[i];
    vect[i] = vect[j];
    vect[j] = tmp;
  }
  return vect;
}

bool vector_sort(std::vector<int> vect) {
  int size = vect.size();
  for (int i = 0; i < size - 1; i++) {
    if (vect[i] > vect[i + 1]) {
      return false;
    }
  }
  return true;
}

std::vector<int> RadixSort(std::vector<int> vect, int size) {
  std::vector<std::vector<int>> vect_start(10);
  std::vector<int> vect1 = vect;
  int tmp = 0;
  int power = 1;
  int max_power;
  if (vector_sort(vect)) {
    return vect;
  }
  max_power = get_max_power(vect);
  while (power <= max_power) {
    for (int i = 0; i < size; i++) {
      tmp = (vect1[i] % static_cast<unsigned int>(pow(10, power)) / static_cast<unsigned int>(pow(10, power - 1)));
      vect_start[tmp].push_back(vect1[i]);
    }
    vect1.clear();
    for (int i = 0; i < 10; i++) {
      if (!vect_start[i].empty()) {
        int size = vect_start[i].size();
        for (int j = 0; j < size; j++) {
          vect1.push_back(vect_start[i][j]);
        }
        vect_start[i].clear();
      }
    }
    power++;
  }
  return vect1;
}
std::vector<int> Merge(const std::vector<int>& vect_left,
                       const std::vector<int>& vect_right) {
  std::vector<int> result((vect_left.size() + vect_right.size()));

  auto const leftSize = static_cast<int>(vect_left.size());
  auto const rightSize = static_cast<int>(vect_right.size());

  auto i = 0, j = 0, k = 0;
  for (k = 0; k < leftSize + rightSize - 1; k++) {
    if (vect_left[i] < vect_right[j])
      result[k] = vect_left[i++];
    else
      result[k] = vect_right[j++];
  }

  while (i < leftSize) {
    result[k++] = vect_left[i++];
  }
  while (j < rightSize) {
    result[k++] = vect_right[j++];
  }

  return result;
}
