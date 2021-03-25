// Copyright 2021 Alekhin Denis

#include <tbb/tbb.h>
#include <iostream>
#include "../../modules/task_3/alekhin_d_simpson_tbb/simpson.h"

double simpsonMethod(std::vector<std::pair<double, double>> scope,
  std::function<double(std::vector<double>)> func,
  int precision) {
  if (scope.size() == 0) {
    throw "Error: scope can't be empty!";
  }
  for (size_t i = 0; i < scope.size(); i++) {
    if (scope[i].first >= scope[i].second) {
      throw "Error: wrong scope interval!";
    }
  }
  if (precision <= 0) {
    throw "Error: precision can't be less than 1";
  }

  int dimention = scope.size();
  std::vector<double>
    h(dimention),
    a(dimention),
    b(dimention);
  for (int i = 0; i < dimention; i++) {
    h[i] = (scope[i].second - scope[i].first) / precision;
    a[i] = scope[i].first;
    b[i] = scope[i].second;
  }

  double evenSum = 0, oddSum = 0;
  std::vector<double> point(a);
  for (int i = 1; i < precision; i++) {
    for (int j = 0; j < dimention; j++) {
      point[j] += h[j];
    }
    if (i % 2 == 0) {
      evenSum += func(point);
    } else {
      oddSum += func(point);
    }
  }

  double result = func(a) + func(b) + 2.0 * evenSum + 4.0 * oddSum;

  for (int i = 0; i < dimention; i++) {
    result *= b[i] - a[i];
  }

  result /= 3.0 * precision;
  return result;
}

double simpsonMethodTBB(
  std::vector<std::pair<double, double>> scope,
  std::function<double(std::vector<double>)> func,
  int precision) {
  if (scope.size() == 0) {
    throw "Error: scope can't be empty!";
  }

  for (size_t i = 0; i < scope.size(); i++) {
    if (scope[i].first >= scope[i].second) {
      throw "Error: wrong scope interval!";
    }
  }
  if (precision <= 0) {
    throw "Error: precision can't be less than 1";
  }

  int dimention = scope.size();
  std::vector<double>
    h(dimention),
    a(dimention),
    b(dimention);
  for (int i = 0; i < dimention; i++) {
    h[i] = (scope[i].second - scope[i].first) / precision;
    a[i] = scope[i].first;
    b[i] = scope[i].second;
  }

  double result =
    tbb::parallel_reduce(tbb::blocked_range<int>(1, precision), 0.0,
    [&](const tbb::blocked_range<int>& range, double result) {
      std::vector<double> oddPoint(dimention), evenPoint(dimention);
      for (int i = range.begin(); i < range.end(); i++) {
        if (i % 2 == 0) {
          for (int j = 0; j < dimention; j++) {
            evenPoint[j] = a[j] + h[j] * i;
          }
          result += 2.0 * func(evenPoint);
        } else {
          for (int j = 0; j < dimention; j++) {
            oddPoint[j] = a[j] + h[j] * i;
          }
          result += 4.0 * func(oddPoint);
        }
      }
      return result;
    }, std::plus<double>());

  result += func(a) + func(b);

  for (int i = 0; i < dimention; i++) {
    result *= b[i] - a[i];
  }

  result /= 3.0 * precision;

  return result;
}
