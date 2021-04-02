// Copyright 2021 Alekhin Denis

#include <omp.h>
#include <iostream>
#include "../../modules/task_2/alekhin_d_simpson_omp/simpson.h"

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

double simpsonMethodOMP(
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

  double result = func(a) + func(b);
  std::vector<double> oddPoint(dimention), evenPoint(dimention);
#pragma omp parallel for reduction(+:result) firstprivate(oddPoint, evenPoint)
  for (int i = 1; i < precision; i += 2) {
    for (int j = 0; j < dimention; j++) {
      oddPoint[j] = a[j] + h[j] * i;
      evenPoint[j] = (i + 1 < precision) ? oddPoint[j] + h[j] : 0;
    }
    result +=  2.0 * func(evenPoint) + 4.0 * func(oddPoint);
  }

  for (int i = 0; i < dimention; i++) {
    result *= b[i] - a[i];
  }

  result /= 3.0 * precision;

  return result;
}
