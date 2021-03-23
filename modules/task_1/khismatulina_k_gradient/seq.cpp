// Copyright 2021 Khismatulina Karina
#include <vector>
#include <cassert>
#include <random>
#include "../../../modules/task_1/khismatulina_k_gradient/seq.h"

std::vector<double> getRandomVector(int size) {
    // assert(size > 0);
    if (size < 0) throw("size ouhgt to be > 0");
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::vector<double> vec(size, 1);
    for (int i = 0; i < size; ++i) {
        vec[i] = mersenne() * mersenne() % 7;
    }
    return vec;
}

std::vector<double> getRandomMatrix(int size) {
    assert(size > 0);
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::vector<double> matrix(size, 1);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i * size + j] = matrix[j * size + i] = mersenne() * mersenne() % 7;
        }
    }
    return matrix;
}

double multVV(std::vector<double> A, std::vector<double> B) {
    assert(A.size() == B.size());
    double result = 0;
    for (size_t i = 0; i < A.size(); ++i) {
        result += A[i] * B[i];
    }
    return result;
}

std::vector<double> multMV(std::vector<double> m, std::vector<double> v) {
    assert(m.size() > 0 && v.size() > 0);
    assert(m.size() % v.size() == 0);
    std::vector<double> result(m.size() / v.size());
    for (size_t i = 0; i < result.size(); ++i) {
        for (size_t j = 0; j < v.size(); ++j) {
            result[i] += m[i * v.size() + j] * v[j];
        }
    }
    return result;
}

std::vector<double> gradientSeq(const std::vector<double>& matrix, const std::vector<double>& vector, int size) {
    assert(size > 0);
    int iters = 0;
    double eps = 0.1, beta = 0.0, alpha = 0.0, check = 0.0;
    std::vector<double> res(size, 1);
    std::vector<double> Ah = multMV(matrix, res);
    std::vector<double> discrepancyCurrent(size), discrepancyNext(size);
    for (int i = 0; i < size; ++i) {
        discrepancyCurrent[i] = vector[i] - Ah[i];
    }
    std::vector<double> h(discrepancyCurrent);
    do {
        iters++;
        Ah = multMV(matrix, h);
        alpha = multVV(discrepancyCurrent, discrepancyNext) / multVV(h, Ah);
        for (int i = 0; i < size; ++i) {
            res[i] += alpha * h[i];
            discrepancyNext[i] = discrepancyCurrent[i] - alpha * Ah[i];
        }
        beta = multVV(discrepancyNext, discrepancyNext) / multVV(discrepancyCurrent, discrepancyCurrent);
        check = sqrt(multVV(discrepancyNext, discrepancyNext));
        for (int k = 0; k < size; ++k) {
            h[k] = discrepancyNext[k] + beta * h[k];
        }
        std::vector<double> swap = discrepancyNext;
        discrepancyNext = discrepancyCurrent;
        discrepancyCurrent = swap;
    } while ((check > eps) && (iters <= size));
    return res;
}
