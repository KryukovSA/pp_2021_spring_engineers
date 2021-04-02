// Copyright 2021 Kochankov Ilya
#include <tbb/tbb.h>
#include <omp.h>
#include <random>
#include <vector>
#include <algorithm>
#include <iostream>
#include "../../../modules/task_3/kochankov_i_shell_sort_simple_tbb/shell_sort_simple_tbb.h"


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


std::vector<double> shell_sort_tbb(const std::vector<double>& vec, int num_threads) {
    if (static_cast<int>(vec.size()) < num_threads) {
        return shell_sort(vec);
    }
    std::vector<double> copy(vec);
    if (vec.size() == 1) {
        return copy;
    }

    int delta = vec.size() / num_threads;

    std::vector<std::vector<double>> split_vec;
    std::vector<double> tmp;

    for (int thread_num = 0; thread_num < num_threads; thread_num++) {
        if (thread_num == num_threads - 1) {
            tmp.insert(tmp.end(), copy.begin() + delta * thread_num, copy.end());
        } else {
            tmp.insert(tmp.end(), copy.begin() + delta * thread_num,
                copy.begin() + delta * (thread_num + 1));
        }
        split_vec.push_back(tmp);
        tmp.clear();
    }

    tbb::task_scheduler_init init(num_threads);

    tbb::parallel_for(tbb::blocked_range<size_t>(0, split_vec.size(), 1),
    [&split_vec](const tbb::blocked_range<size_t>& range){
        for (size_t i = range.begin(); i != range.end(); ++i) {
            split_vec[i] = shell_sort(split_vec[i]);
        }
    }, tbb::simple_partitioner());

    std::vector<double> merged = split_vec[0];
    // std::copy(merged.begin(), merged.end(), std::ostream_iterator<double>(std::cout, " "));
    for (size_t i = 1; i < split_vec.size(); ++i) {
        merged = merge(merged, split_vec[i]);
    }

    return merged;
}
