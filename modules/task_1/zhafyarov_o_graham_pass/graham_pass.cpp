// Copyright 2021 Zhafyarov Oleg
#include "../../../modules/task_1/zhafyarov_o_graham_pass/graham_pass.h"
#include <time.h>
#include <random>
#include <vector>
#include <algorithm>

std::vector<point> RandomVector(int size) {
  bool flag = false;
  std::vector<point> vec_tmp(size);
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));
  for (int i = 0; i < size; i++) {
    vec_tmp[i].x = gen() % 150;
    vec_tmp[i].y = gen() % 100;
  }
  while (!flag) {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        if (i == j) {
          continue;
        }
        if (vec_tmp[i].x == vec_tmp[j].x && vec_tmp[i].y == vec_tmp[j].y) {
          vec_tmp[i].x = gen() % 150;
          vec_tmp[i].y = gen() % 100;
          i = 0;
          j = 0;
        }
      }
    }
    flag = true;
  }
  return vec_tmp;
}

double Rotation(point a, point b, point c) {
  return((b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x));
}

std::vector<size_t> GrahamPass(const std::vector<point>& basis_vec,
  int* count) {
  std::vector<size_t> result;

  if (basis_vec.size() == 1)  return result;

  std::vector<int> vec_tmp;

  int min = 0;

  for (int i = 1; i < static_cast<int>(basis_vec.size()); i++) {
    min = basis_vec.at(min).x > basis_vec.at(i).x ||
      (basis_vec.at(min).x == basis_vec.at(i).x &&
      basis_vec.at(min).y > basis_vec.at(i).y) ? i : min;
  }

  vec_tmp.push_back(min);

  for (int i = 0; i < static_cast<int>(basis_vec.size()); i++) {
    if (i == min) {
      continue;
    }
    vec_tmp.push_back(i);
  }

  for (int i = 2; i < static_cast<int>(basis_vec.size()); i++) {
    int j = i;
    while (j > 1 && Rotation(basis_vec.at(min), basis_vec.at(vec_tmp.at(j - 1)),
      basis_vec.at(vec_tmp.at(j))) < 0) {
      std::swap(vec_tmp.at(j), vec_tmp.at(j - 1));
      j--;
    }
  }

  result.push_back(vec_tmp.at(0));
  result.push_back(vec_tmp.at(1));

  for (int i = 2; i < static_cast<int>(basis_vec.size()); i++) {
    while (Rotation(basis_vec.at(result.at(result.size() - 2)),
      basis_vec.at(result.at(result.size() - 1)),
      basis_vec.at(vec_tmp.at(i))) < 0) {
      result.pop_back();
    }
    result.push_back(vec_tmp.at(i));
  }

  *count = static_cast<int>(result.size());

  return result;
}
