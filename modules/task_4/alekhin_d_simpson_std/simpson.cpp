// Copyright 2021 Alekhin Denis

#include <omp.h>
#include <iostream>
#include "../../../modules/test_tasks/test_std/ops_std.h"
#include "../../../3rdparty/unapproved/unapproved.h"
#include "../../modules/task_4/alekhin_d_simpson_std/simpson.h"

std::mutex mutex;

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
      point[j] = a[j] + h[j] * i;
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

double globEvenSum = 0;
double globOddSum = 0;

void calcPoints(std::function<double(std::vector<double>)> func,
  std::vector<double> a, std::vector<double> h,
  int startPoint, int endPoint) {
  double evenSum = 0, oddSum = 0;
  int dimention = a.size();
  std::vector<double> point(a);
  for (int i = startPoint; i < endPoint; i++) {
    for (int j = 0; j < dimention; j++) {
      point[j] = a[j] + h[j] * (i + 1);
    }
    if (i % 2 == 0) {
      oddSum += func(point);
    } else {
      evenSum += func(point);
    }
  }
  std::lock_guard<std::mutex> lock(mutex);
  globEvenSum += evenSum;
  globOddSum += oddSum;
}

double simpsonMethodSTD(
  std::vector<std::pair<double, double>> scope,
  std::function<double(std::vector<double>)> func,
  int precision) {
  globOddSum = 0;
  globEvenSum = 0;
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

  int threadNumber = std::thread::hardware_concurrency();
  std::vector<std::thread> threads;

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

  int d = (precision - 1) / threadNumber;
  int r = (precision - 1) % threadNumber;
  std::vector<double> numberOfTasks(threadNumber);
  for (int thread = 0; thread < threadNumber; thread++) {
    if (r != 0) {
      numberOfTasks[thread] = d + 1;
      r--;
    } else {
      numberOfTasks[thread] = d;
    }
  }

  std::vector<std::pair<double, double>> threadScope(dimention);
  int countOfSharedTasks = 0;
  for (int thread = 0; thread < threadNumber; thread++) {
    threads.push_back(std::thread(calcPoints, func, a, h,
      countOfSharedTasks, countOfSharedTasks + numberOfTasks[thread]));
    countOfSharedTasks += numberOfTasks[thread];
  }
  for (int thread = 0; thread < threadNumber; thread++) {
    threads[thread].join();
  }

  double result = func(a) + func(b) + 2.0 * globEvenSum + 4.0 * globOddSum;

  for (int i = 0; i < dimention; i++) {
    result *= b[i] - a[i];
  }

  result /= 3.0 * precision;

  return result;
}
