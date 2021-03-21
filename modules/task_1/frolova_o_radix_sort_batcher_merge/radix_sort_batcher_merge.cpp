// Copyright 2021 Frolova Olga
#include <math.h>
#include <random>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include "../../../modules/task_1/frolova_o_radix_sort_batcher_merge/radix_sort_batcher_merge.h"


std::vector<double> getRandomVector(int size) {
    std::vector<double> vec(size);
    std::mt19937 gen;
    gen.seed(static_cast<unsigned char>(time(0)));
    for (int i = 0; i < size; i++) {
        vec[i] = gen() / 10000;
    }
    return vec;
}

int countRadix(double num) {
    int res = 0;
    while (static_cast<int>(num) > 0) {
        num = num / 10;
        res++;
    }
    return res;
}

std::vector<double> checkVector(std::vector<double> vec) {
    int j = 0;
    double tmp = 0;
    int lengh = static_cast<int>(vec.size());
    for (int i = 0; i < lengh; i++) {
        j = i;
        for (int k = i; k < lengh; k++) {
            if (vec[j] > vec[k]) {
                j = k;
            }
        }
        tmp = vec[i];
        vec[i] = vec[j];
        vec[j] = tmp;
    }
    return vec;
}

double maxVal(std::vector<double> vec) {
    int size = static_cast<int>(vec.size());
    double res = vec[0];
    for (int i = 1; i < size; i++)
        if (res < vec[i]) res = vec[i];
    return res;
}

int countNegRadix(double num) {
    std::string str_num = std::to_string(num);
    if (str_num.find('.')) {
        while (str_num[str_num.size() - 1] == '0')  str_num.erase(str_num.size() - 1);
        return static_cast<int>(str_num.size()) - static_cast<int>(str_num.find('.')) - 1;
    } else {
        return 0;
    }
}

int getRemainder(double num) {
    int rad = countNegRadix(num);
    if (rad == 0) return 0;
    return static_cast<int>(round((((num - static_cast<int>(num)) * pow(10, rad)))));
}

std::vector<double> radixSortNeg(std::vector<double> vec, int radix) {
    std::vector<int> counts(10, 0);
    std::vector<int> counts1(10, 0);
    std::vector<double> res(vec.size());
    int size = static_cast<int>(vec.size());
    for (int i = 0; i < size; i++) {
        int r = getRemainder(vec[i]);
        counts[static_cast<int>((((r) % static_cast<unsigned int>(pow(10, (radix)))) / pow(10, (radix - 1))))]++;
    }
    for (int i = 1; i < 10; i++)
         for (int j = i - 1; j >= 0; j--)
             counts1[i] += counts[j];
    for (int i = 0; i < size; i++) {
        int r = getRemainder(vec[i]);
        int index = static_cast<int>((((r) % static_cast<unsigned int>(pow(10, (radix)))) / pow(10, (radix - 1))));
        res[counts1[index]] = vec[i];
        counts1[index]++;
    }
    return res;
}

std::vector<double> radixSortPos(std::vector<double> vec, int radix) {
    std::vector<int> counts(10, 0);
    std::vector<int> counts1(10, 0);
    std::vector<double> res(vec.size());
    int size = static_cast<int>(vec.size());
    for (int i = 0; i < size; i++) {
        int step = (static_cast<int>(vec[i]) % static_cast<unsigned int>(pow(10, (radix))));
        counts[static_cast<int>((step / pow(10, (radix - 1))))]++;
    }
    for (int i = 1; i < 10; i++)
        for (int j = i - 1; j >= 0; j--)
            counts1[i] += counts[j];
    for (int i = 0; i < size; i++) {
        int step = (static_cast<int>(vec[i]) % static_cast<unsigned int>(pow(10, (radix))));
        int index = static_cast<int>((step / pow(10, (radix - 1))));
        res[counts1[index]] = vec[i];
        counts1[index]++;
    }
    return res;
}

std::vector<double> radixSort(std::vector<double> vec) {
    int size = static_cast<int>(vec.size());
    int maxRadNeg = 0;
    int maxRadPos = countRadix(maxVal(vec));
    std::vector<double> res;
    for (int i = 0; i < size; i++)
        if (countNegRadix(vec[i]) > maxRadNeg) maxRadNeg = countNegRadix(vec[i]);
    if (maxRadNeg != 0) {
        res = radixSortNeg(vec, 1);
        if (maxRadNeg > 1) {
            for (int j = 2; j <= maxRadNeg; j++)
                res = radixSortNeg(res, j);
        }
        for (int radix = 1; radix <= maxRadPos; radix++)
            res = radixSortPos(res, radix);
    } else {
        res = radixSortPos(vec, 1);
        for (int radix = 2; radix <= maxRadPos; radix++)
            res = radixSortPos(res, radix);
    }
    return res;
}


