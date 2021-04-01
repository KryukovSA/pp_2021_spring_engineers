// Copyright 2021 Solomakhin Sergey
#include "../../../modules/task_1/solomakhin_s_hoar_sort_simple_merge/hoar_sort_simple_merge.h"
#include <random>
#include <algorithm>
#include <ctime>
#include <utility>
#include <vector>

std::vector<int> random_gen(int size) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<int> vec(size);
    for (int i = 0; i < size; i++) {
        vec[i] = gen() % 100;
    }
    return vec;
}

void hoar_sort(int left, int right, std::vector <int>* arr) {
    while (right > left) {
        int it_l = left;
        int it_r = right;
        double pivot = arr->at((left + right) / 2);

        while (it_l <= it_r) {
            while (arr->at(it_l) < pivot) {
                it_l++;
            }
            while (arr->at(it_r) > pivot) {
                it_r--;
            }
            if (it_l <= it_r) {
                std::swap(arr->at(it_l), arr->at(it_r));
                it_l++;
                it_r--;
            }
        }

        if (2 * it_l > left + right) {
            hoar_sort(it_l, right, arr);
            right = it_l - 1;
        } else {
            hoar_sort(left, it_l - 1, arr);
            left = it_l;
        }
    }
    return;
}

bool checker(std::vector <int>* vec) {
    return std::is_sorted((vec)->begin(), (vec)->end());
}

std::vector<int>merge(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> result((a.size() + b.size()));

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
