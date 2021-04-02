// Copyright 2021 Bulychev Andrey
#include <random>
#include <vector>
#include <ctime>
#include <algorithm>
#include "../../../modules/task_1/bulychev_a_shell_sort_simple/shell_sort_simple.h"


std::vector<double> getRandomVector(int size) {
    if (size < 0) {
        throw "Error size";
    }
    std::vector<double> vec(size);
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    for (int  i = 0; i < size; i++) vec[i] = gen() % 10000;
    return vec;
}

std::vector<double> Shell_sort(const std::vector<double>& vec) {
    std::vector<double> tmp(vec);
    for (int step = tmp.size() / 2; step != 0; step /= 2) {
        for (int i = step; i < static_cast<int>(tmp.size()); i++) {
            for (int j = i - step; j >= 0 && tmp[j] > tmp[j + step]; j -= step) {
                double aV = tmp[j];
                tmp[j] = tmp[j + step];
                tmp[j + step] = aV;
            }
        }
    }
    return tmp;
}

std::vector<double> Merge(const std::vector<double>& vec1, const std::vector<double>& vec2) {
    int size1 = vec1.size();
    int size2 = vec2.size();
    std::vector<double> tmp(size1 + size2);
    int i = 0, j = 0;
    for (int k = 0; k < size1 + size2; k++) {
        if (i > size1 - 1) {
            double a = vec2[j];
            tmp[k] = a;
            j++;
        } else {
            if (j > size2 - 1) {
                double a = vec1[i];
                tmp[k] = a;
                i++;
            } else {
                if (vec1[i] < vec2[j]) {
                    double a = vec1[i];
                    tmp[k] = a;
                    i++;
                } else {
                    double b = vec2[j];
                    tmp[k] = b;
                    j++;
                }
            }
        }
    }
    return tmp;
}
