// Copyright 2021 Boytsov Vladislav
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <ctime>
#include "../../modules/task_1/boytsov_v_monte_carlo/monte_carlo.h"

double getSequentialOperations(double(*f)(std::vector<double>), const std::vector<double>&a,
const std::vector<double>&b, int n) {
    if (n <= 0)
      throw "n is negative";
    double res = 0.0;
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    int multiplicity = a.size();
    double S = 1;
    for (int i = 0; i < multiplicity; i++)
      S *= (b[i] - a[i]);
    std::vector<std::uniform_real_distribution<double>> r(multiplicity);
    std::vector<double> r1(multiplicity);
    for (int i = 0; i < multiplicity; i++)
      r[i] = std::uniform_real_distribution<double>(a[i], b[i]);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < multiplicity; j++)
        r1[j] = r[j](gen);
      res += f(r1);
    }
    res *= S / n;
    return res;
}

