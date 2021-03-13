// Copyright 2021 Alekhin Denis

#include "../../modules/task_1/alekhin_d_simpson/simpson.h"

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

  int countOfDimentions = scope.size();
  std::vector<double> h(countOfDimentions);
  double hComp = 1;
  for (size_t i = 0; i < countOfDimentions; i++) {
    h[i] = (scope[i].second - scope[i].first) / precision;
    hComp *= h[i];
  }

  double evenSum = 0, oddSum = 0;
  std::vector<double> point(countOfDimentions);
  for (size_t i = 1; i < precision; i++) {
    for (size_t j = 0; j < countOfDimentions; j++) {
      point[j] = scope[j].first + h[j] * i;
    }
    if (i % 2 == 0) {
      evenSum += func(point);
    } else {
      oddSum += func(point);
    }
  }

  std::vector<double> a(countOfDimentions), b(countOfDimentions);
  for (size_t i = 0; i < countOfDimentions; i++) {
    a[i] = scope[i].first;
    b[i] = scope[i].second;
  }

  double result = hComp * (func(a) + func(b) + 2.0 * evenSum + 4.0 * oddSum) / 3.0;

  return result;
}
