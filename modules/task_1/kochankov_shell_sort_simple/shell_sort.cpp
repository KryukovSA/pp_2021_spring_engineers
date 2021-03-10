#include <random>
#include <vector>
#include "shell_sort.h"


std::vector<double> getRandomVector(int sz) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<double> vec(sz);
    for (int  i = 0; i < sz; i++) { vec[i] = gen() % 100; }
    return vec;
}

std::vector<double> shell_sort(const std::vector<double>& vec) {
    std::vector<double> copy(vec);
    for (int step = copy.size() / 2; step != 0; step /= 2) {
        for (int i = step; i < int(copy.size()); i++) {
            for (int j = i - step; j >= 0 && copy[j] > copy[j + step]; j -= step) {
                double x = copy[j];
                copy[j] = copy[j + step];
                copy[j + step] = x;
            }
        }
    }
    return copy;
}

std::vector<double> merge(const std::vector<double>& a, const std::vector<double>& b) {
    std::vector<double> result((a.size() + b.size()));

    int i = 0, j = 0, k = 0;
    while (i < static_cast<int>(a.size()) && j < static_cast<int>(b.size())) {
        if (a[i] < b[j])
            result[k] = a[i++];
        else
            result[k] = b[j++];
        k++;
    }
    while (i < static_cast<int>(a.size())) {
        result[k++] = a[i++];
    }
    while (j < static_cast<int>(b.size())) {
        result[k++] = b[j++];
    }

    return result;
}