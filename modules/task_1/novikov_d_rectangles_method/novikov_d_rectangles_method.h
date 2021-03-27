// Copyright 2021 Novikov Danil
#ifndef MODULES_TASK_1_NOVIKOV_D_RECTANGLES_METHOD_NOVIKOV_D_RECTANGLES_METHOD_H_
#define MODULES_TASK_1_NOVIKOV_D_RECTANGLES_METHOD_NOVIKOV_D_RECTANGLES_METHOD_H_

#include <cstring>
#include <cmath>
#include <vector>
#include <iostream>

template <typename Function>
double rectangles_base(Function function, std::vector <double> begin_point,
    std::vector <double> end_point, const int number_of_partitions) {
    if (number_of_partitions <= 0) {
        throw 1;
    }

    if (begin_point.size() != end_point.size()) {
        throw 1;
    }

    int dimension = begin_point.size();
    std::vector<double> h(dimension);

    for (int i = 0; i < dimension; ++i) {
        h[i] = (end_point[i] - begin_point[i]) /
        static_cast<double>(number_of_partitions);
    }
    std::vector <double> half_point(dimension);
    double result = 0.0;
    int k;
    int sectors = std::pow(number_of_partitions, dimension);
    for (int i = 0; i < sectors; ++i) {
        for (k = 0; k < dimension; k++) {
            int a = std::pow(number_of_partitions, k+1);
            int b = (number_of_partitions * k == 0 ? 1 :
                     std::pow(number_of_partitions, k));
            int p = (i % a) / b;
            half_point[k] = begin_point[k] + h[k] * p + h[k] * 0.5;
        }
        result += function(half_point);
    }
    for (int i = 0; i < dimension; ++i) {
        result *= h[i];
    }
    return result;
}


#endif  // MODULES_TASK_1_NOVIKOV_D_RECTANGLES_METHOD_NOVIKOV_D_RECTANGLES_METHOD_H_
