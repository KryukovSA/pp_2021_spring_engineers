// Copyright 2021 Ekaterina Burmistrova

#include <omp.h>
#include <vector>
#include <string>
#include <random>
#include <iostream>
#include <functional>
#include "./../../modules/task_1/bourmistrova_e_tr_int/trapezoid_integral.h"

double CheckCoeff(int i, const std::pair<int, int>& pair) {
    double qju = 1.00;
    if (i == pair.first || i == pair.second)
        qju *= 0.5;
    return qju;
}
double SolveSequential(const std::vector<std::pair<int, int>>& bord,
    std::function<double(double, double, double)> f) {
    double sum = 0;
    int i = 0, j = 0, k = 0;
    if (bord.size() == 1) {  // ONE DIMENSION
        // int h = (bord[0].second.second
        // - bord[0].second.first) / num_threads;
        for (i = bord[0].first; i < bord[0].second; i++) {
            sum += ((f(i, 1, 1) + f(i + 1, 1, 1)) / 2);
        }
    } else if (bord.size() == 2) {  // TWO DIMENSIONS
        double q0 = 1, q1 = 1;
        // int h1 = (bord[0].second.second
        // - bord[0].second.first) / num_threads;
        // int h2 = (bord[1].second.second
        // - bord[1].second.first) / num_threads;
        for (i = bord[0].first; i < bord[0].second+1; i++) {
            // q = 1;
            q0 = CheckCoeff(i, bord[0]);
            for (j = bord[1].first; j < bord[1].second+1; j++) {
                    q1 = CheckCoeff(j, bord[1]);
                    sum += q0 * q1 * f(i, j, 1);
            }
        }
    } else {  // THREE DIMENSIONS
        double q0 = 1, q1 = 1, q2 = 1;
        // int h1 = (bord[0].second.second
        // - bord[0].second.first) / num_threads;
        // int h2 = (bord[1].second.second
        // - bord[1].second.first) / num_threads;
        // int h3 = (bord[2].second.second
        // - bord[2].second.first) / num_threads;
        for (i = bord[0].first; i < bord[0].second + 1; i++) {
            q0 = CheckCoeff(i, bord[0]);
            for (j = bord[1].first; j < bord[1].second + 1; j++) {
                q1 = CheckCoeff(j, bord[1]);
                for (k = bord[2].first; k < bord[2].second + 1; k++) {
                        q2 = CheckCoeff(k, bord[2]);
                        sum += q0 * q1 * q2 * f(i, j, k);
                }
            }
        }
    }
    return sum;
}
