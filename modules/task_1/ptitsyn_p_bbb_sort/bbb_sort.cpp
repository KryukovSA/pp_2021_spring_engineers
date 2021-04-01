// Copyright 2021 Ptitsyn Pavel
#include <math.h>
#include <random>
#include <vector>
#include <cstring>
#include <utility>
#include <cstdlib>
#include <iostream>
#include "../../../modules/task_1/ptitsyn_p_bbb_sort/bbb_sort.h"

double RandomDouble::Next() {
    static RandomDouble rand = RandomDouble();
    return rand.dist_(rand.gen_);
}

RandomDouble::RandomDouble() : gen_(std::random_device()()), dist_(-1e3, 1e3) {}

std::vector<double> random_double_array(size_t size) {
    std::vector<double> arr(size);

    for (size_t i = 0; i < size; ++i) {
        arr[i] = RandomDouble::Next();
    }

    return arr;
}

void bitwise_sort_mod(BitsetIt first, BitsetIt last,
    size_t bit, bool positive = true) {
    auto le = first, ri = last;
    if (le >= ri || le + 1 == ri) return;

    while (le < last && ((*le)[bit] != positive)) ++le;
    if (le == last) {
        if (bit == 0u) return;
        bitwise_sort_mod(first, last, bit - 1u, positive);
        return;
    }

    --ri;
    while (le < ri) {
        while (le < ri && ((*ri)[bit] == positive)) --ri;
        if (le == ri) break;

        std::swap(*le, *ri);
        while (le < ri && ((*le)[bit] != positive)) ++le;
    }

    if (bit == 0u) return;
    bitwise_sort_mod(first, le, bit - 1u, positive);
    bitwise_sort_mod(le, last, bit - 1u, positive);
}

void bitwise_sort(BitsetIt first, BitsetIt last) {
    auto le = first, ri = last;
    if (le >= ri || le + 1 == ri) return;

    while (le < last && (*le)[63u]) ++le;
    if (le == last) {
        bitwise_sort_mod(first, last, 62u, false);
        return;
    }

    --ri;
    while (le < ri) {
        while (le < ri && !(*ri)[63u]) --ri;
        if (le == ri) break;

        std::swap(*le, *ri);
        while (le < ri && (*le)[63u]) ++le;
    }

    bitwise_sort_mod(first, le, 62u, false);
    bitwise_sort_mod(le, last, 62u, true);
}

void radix_sort(DoubleIt first, DoubleIt last) {
    if (first >= last) return;

    std::vector<std::bitset<64>> bits(last - first);
    auto it = first;
    for (size_t i = 0u; i < bits.size(); ++it, ++i) {
        double double_repr = *it;
        uint64_t int_repr;
        std::memcpy(&int_repr, &double_repr, 8u);
        bits[i] = int_repr;
    }

    bitwise_sort(bits.begin(), bits.end());

    it = first;
    for (size_t i = 0; i < bits.size(); ++it, ++i) {
        double double_repr;
        uint64_t int_repr = bits[i].to_ullong();
        std::memcpy(&double_repr, &int_repr, 8u);
        *it = double_repr;
    }
}

std::vector<double> EvenOddBatch(std::vector<double> vec1,
    std::vector<double> vec2) {
    int size1 = vec1.size();
    int size2 = vec2.size();
    int size = size1 + size2;
    std::vector<double> res(size);
    int i = 0, j = 0, k = 0;

    while ((j < size1) && (k < size2)) {
        res[i] = vec1[j];
        res[i + 1] = vec2[k];
        i += 2;
        j++;
        k++;
    }

    if ((k >= size2) && (j < size1)) {
        for (int l = i; l < size; l++) {
            res[l] = vec1[j];
            j++;
        }
    }

    for (int i = 0; i < size - 1; i++) {
        if (res[i] > res[i + 1]) {
            std::swap(res[i], res[i + 1]);
        }
    }

    return res;
}

std::vector<double> evenBatch(std::vector<double> vec1,
    std::vector<double> vec2) {
    int size1 = vec1.size();
    int size2 = vec2.size();
    int res_size = size1 / 2 + size2 / 2 + size1 % 2 + size2 % 2;
    std::vector<double> res(res_size);
    int i1 = 0;
    int i2 = 0;
    int i = 0;

    while ((i1 < size1) && (i2 < size2)) {
        if (vec1[i1] <= vec2[i2]) {
            res[i] = vec1[i1];
            i1 += 2;
        } else {
            res[i] = vec2[i2];
            i2 += 2;
        }
        i++;
    }

    if (i1 >= size1) {
        for (int l = i2; l < size2; l += 2) {
            res[i] = vec2[l];
            i++;
        }
    } else {
        for (int l = i1; l < size1; l += 2) {
            res[i] = vec1[l];
            i++;
        }
    }
    radix_sort(res.begin(), res.end());
    return res;
}

std::vector<double> oddBatch(std::vector<double> vec1,
    std::vector<double> vec2) {
    int size1 = vec1.size();
    int size2 = vec2.size();
    int res_size = size1 / 2 + size2 / 2;
    std::vector<double> res(res_size);
    int i1 = 1;
    int i2 = 1;
    int i = 0;

    while ((i1 < size1) && (i2 < size2)) {
        if (vec1[i1] <= vec2[i2]) {
            res[i] = vec1[i1];
            i1 += 2;
        } else {
            res[i] = vec2[i2];
            i2 += 2;
        }
        i++;
    }

    if (i1 >= size1) {
        for (int l = i2; l < size2; l += 2) {
            res[i] = vec2[l];
            i++;
        }
    } else {
        for (int l = i1; l < size1; l += 2) {
            res[i] = vec1[l];
            i++;
        }
    }
    radix_sort(res.begin(), res.end());
    return res;
}

void print(std::vector<double> const& a) {
    std::cout << "The vector elements are : ";

    for (unsigned int i = 0; i < a.size(); i++) std::cout << a.at(i) << ' ';

    std::cout << std::endl;
}
