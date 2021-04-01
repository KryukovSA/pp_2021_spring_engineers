// Copyright 2021 Gorbunova Valeria
#include <stdio.h>
#include "../../../modules/task_1/gorbunova_v_conjugate_gradient/conjugate_gradient.h"

double conj_grad(double** A, double* B, int S) {
    double* x = new double[S];
    double* d = new double[S];
    double* r = new double[S];
    double* Ax = new double[S];
    double alpha, beta, sumB, num, R, den;
    int i, j, IterNum = 1;
    double MaxIteration = 200;
    for (i = 0; i < S; i++) {
        x[i] = 1;
    }
    for (i = 0; i < S; i++) {
        for (Ax[i] = 0, j = 0; j < S; j++)
            Ax[i] += A[i][j] * x[j];
        r[i] = B[i] - Ax[i];
        d[i] = r[i];
    }
    for (sumB = 0, i = 0; i < S; i++) {
        sumB += B[i] * B[i];
    }
    int Iteration = 0;
    do {
        Iteration++;
        num = 0;
        den = 0;
        for (i = 0; i < S; i++) {
            for (Ax[i] = 0, j = 0; j < S; j++) {
                Ax[i] += A[i][j] * d[j];
            }
            num += r[i] * r[i];
            den += Ax[i] * d[i];
        }
        alpha = num / den;
        R = 0;
        for (i = 0; i < S; i++) {
            x[i] += alpha * d[i];
            r[i] -= alpha * Ax[i];
            R += r[i] * r[i];
        }
        IterNum++;
        beta = R / num;
        for (i = 0; i < S; i++)
            d[i] = r[i] + beta * d[i];
    } while (R / sumB > 0.01 * 0.01 && Iteration < MaxIteration);
    delete[] Ax;
    for (int i = 0; i < S; i++)
        delete[] A[i];
    delete[] A;
    delete[] B;
    delete[] d;
    delete[] r;
    double res = 0;
    for (i = 0; i < S; i++) {
        res += x[i];
    }
    delete[] x;
    return res;
}
