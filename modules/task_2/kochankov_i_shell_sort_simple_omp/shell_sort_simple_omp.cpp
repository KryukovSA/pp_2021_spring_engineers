// Copyright 2021 Kochankov Ilya
#include <omp.h>
#include <random>
#include <vector>
#include <algorithm>
#include <iostream>
#include "../../../modules/task_2/kochankov_i_shell_sort_simple_omp/shell_sort_simple_omp.h"


std::vector<double> getRandomVector(int sz) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<double> vec(sz);
    for (int i = 0; i < sz; i++) { vec[i] = gen() % 100; }
    return vec;
}

std::vector<double> shell_sort(const std::vector<double>& vec) {
    std::vector<double> copy(vec);
    for (int step = copy.size() / 2; step != 0; step /= 2) {
        for (int i = step; i < static_cast<int>(copy.size()); i++) {
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


std::vector<double> shell_sort_omp(const std::vector<double>& vec, int num_threads) {
    if (static_cast<int>(vec.size()) < num_threads) {
        return shell_sort(vec);
    }
    std::vector<double> copy(vec);
    if (vec.size() == 1) {
        return copy;
    }
    omp_set_num_threads(num_threads);

    int delta = vec.size() / num_threads;
    std::vector<double> local_vec;

#pragma omp parallel private(local_vec) shared(copy, delta)
    {
        int thread_num = omp_get_thread_num();
        if (thread_num == num_threads - 1) {
            local_vec = std::vector<double>(copy.size() - delta * (num_threads - 1));
        } else {
            local_vec = std::vector<double>(delta);
        }

        if (thread_num == num_threads - 1) {
            std::copy(copy.begin() + delta * (num_threads - 1), copy.end(), local_vec.begin());
        } else {
            std::copy(copy.begin() + delta * thread_num,
                copy.begin() + delta * (thread_num + 1), local_vec.begin());
        }
        local_vec = shell_sort(local_vec);

#pragma omp barrier
        if (thread_num == 0) {
            copy = local_vec;
        }

#pragma omp barrier
#pragma omp critical
        if (thread_num != 0) {
            copy = merge(copy, local_vec);
        }
    }
    return copy;
}
