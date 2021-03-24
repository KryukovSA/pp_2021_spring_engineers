// Copyright 2021 Dmitry Ryazanov
#include "../../../modules/task_1/ryazanov_d_shell_and_batcher/ryazanov_d_shell_and_batcher.h"
#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

std::vector<int> getRandomVector(int sz) {
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));
  std::vector<int> vec(sz);
  for (int i = 0; i < sz; i++) {
    vec[i] = gen() % 100;
  }
  return vec;
}

void print(std::vector<int> const &a) {
  std::cout << "The vector elements are : ";

  for (unsigned int i = 0; i < a.size(); i++) std::cout << a.at(i) << ' ';

  std::cout << std::endl;
}

std::vector<int> SortShell(const std::vector<int> &vec) {
  std::vector<int> res(vec);
  for (int step = res.size() / 2; step != 0; step /= 2) {
    for (int i = step; i < static_cast<int>(res.size()); i++) {
      for (int j = i - step; j >= 0 && res[j] > res[j + step]; j -= step) {
        int tmp = res[j];
        res[j] = res[j + step];
        res[j + step] = tmp;
      }
    }
  }
  return res;
}

std::vector<int> sh(const std::vector<int> &vec, int l, int r) {
  std::vector<int> aux, res;
  res = vec;
  int m = (l + r) / 2;

  if (res.size() % 2 != 0) {
    int lValue = res.at(res.size() - 1);

    res.erase(res.end() - 1);

    for (int j = l; j < (r - 1) / 2; j++) {
      aux.push_back(res.at(j));
      aux.push_back(res.at(j + m));
    }

    aux.push_back(lValue);
  } else {
    for (int j = l; j < r / 2; j++) {
      aux.push_back(res.at(j));
      aux.push_back(res.at(j + m));
    }
  }

  res.erase(res.begin(), res.end());
  res.shrink_to_fit();

  for (int i = l; i < r; i++) {
    res.push_back(aux[i]);
  }
  res = SortShell(res);

  return res;
}

std::vector<int> uns(const std::vector<int> &vec, int l, int r) {
  std::vector<int> auxLeft, auxRight, res;
  res = vec;
  if (res.size() % 2 != 0) {
    int lValue = res.at(res.size() - 1), lPos = res.size() - 1;

    res.erase(res.end() - 1);

    for (int j = l; j < r - 1; j += 2) {
      auxLeft.push_back(res.at(j));
      auxRight.push_back(res.at(j + 1));
    }

    if (lPos % 2 == 0)
      auxLeft.push_back(lValue);
    else
      auxRight.push_back(lValue);
  } else {
    for (int j = l; j < r; j += 2) {
      auxLeft.push_back(res.at(j));
      auxRight.push_back(res.at(j + 1));
    }
  }

  res.erase(res.begin(), res.end());
  res.shrink_to_fit();

  res.reserve(auxLeft.size() + auxRight.size());
  res.insert(res.end(), auxLeft.begin(), auxLeft.end());
  res.insert(res.end(), auxRight.begin(), auxRight.end());

  return res;
}

std::vector<int> BatcherSort(const std::vector<int> &vec) {
  if (vec.size() == 2) SortShell(vec);
  if (vec.size() == 1) return vec;
  std::vector<int> vecAuxLeft, vecAuxRight, res;
  res = vec;
  vecAuxLeft.reserve(vec.size() / 2);
  vecAuxRight.reserve(vec.size() / 2);
  res = uns(res, 0, res.size());
  vecAuxLeft.insert(vecAuxLeft.end(), res.begin(),
                    res.begin() + res.size() / 2);
  vecAuxRight.insert(vecAuxRight.end(), res.begin() + res.size() / 2,
                     res.end());
  vecAuxLeft = BatcherSort(vecAuxLeft);
  vecAuxRight = BatcherSort(vecAuxRight);
  res.erase(res.begin(), res.end());
  res.shrink_to_fit();
  res.insert(res.end(), vecAuxLeft.begin(), vecAuxLeft.end());
  res.insert(res.end(), vecAuxRight.begin(), vecAuxRight.end());
  res = sh(res, 0, res.size());
  return res;
}
