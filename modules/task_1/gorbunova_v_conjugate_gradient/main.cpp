// Copyright 2021 Gorbunova Valeria
#include <stdio.h>
#include <gtest/gtest.h>
#include "./conjugate_gradient.h"

TEST(Conj_Grad, test_1) {
    int S = 3;
    double C[9] = {4, -1, 2, -1, 6, -2, 2, -2, 5 };
    double** A = new double* [S];
    for (int count = 0; count < S; count++)
       A[count] = new double[S];
    int k = 0;
    for (int i = 0; i < S; i++)
        for (int j = 0; j < S; j++) {
            A[i][j] = C[k];
            k++;
        }
    double* B = new double[S];
    B[0] = -1;
    B[1] = 9;
    B[2] = -10;
    double res = 1 + 1 - 2;
    ASSERT_NEAR(res, conj_grad(A, B, S), 0.5);
}

TEST(Conj_Grad, test_2) {
    int S = 2;
    double C[4] = {3, -1, -1, 3 };
    double** A = new double* [S];
    for (int count = 0; count < S; count++)
        A[count] = new double[S];
    int k = 0;
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < S; j++) {
            A[i][j] = C[k];
            k++;
        }
    }
    double* B = new double[S];
    B[0] = 3;
    B[1] = 7;
    double res = 2 + 3;
    ASSERT_NEAR(res, conj_grad(A, B, S), 0.5);
}

TEST(Conj_Grad, test_3) {
    int S = 3;
    double C[9] = {13.14, -2.12, 1.17, -2.12, 6.3, -2.45, 1.17, -2.45, 4.6};
    double** A = new double* [S];
    for (int count = 0; count < S; count++) {
        A[count] = new double[S];
    }
    int k = 0;
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < S; j++) {
            A[i][j] = C[k];
            k++;
        }
    }

    double* B = new double[S];
    B[0] = 1.27;
    B[1] = 2.13;
    B[2] = 3.14;
    double res = 0.13 + 0.8 + 1.1;
    ASSERT_NEAR(res, conj_grad(A, B, S), 0.5);
}



TEST(Conj_Grad, test_4) {
    int S = 4;
    double C[16] = {5.23, 0.14, 0.30, 0.40, 0.14, 7.32, 0.22, 0.24, 0.30, 0.22, -9.2, 0.31, 0.4, 0.24, 0.31, -4.17};
    double** A = new double* [S];
    for (int count = 0; count < S; count++)
        A[count] = new double[S];
    int k = 0;
    for (int i = 0; i < S; i++)
        for (int j = 0; j < S; j++) {
            A[i][j] = C[k];
            k++;
        }
    double* B = new double[S];
    B[0] = 1.02;
    B[1] = 1;
    B[2] = 1.34;
    B[3] = 1.27;
    double res = 0.22 + 0.14 - 0.14 - 0.28;
    ASSERT_NEAR(res, conj_grad(A, B, S), 0.5);
}

TEST(Conj_Grad, test_5) {
    int S = 3;
    double C[9] = {10, 2, 1, 2, 10, 3, 1, 3, 10};
    double** A = new double* [S];
    for (int count = 0; count < S; count++)
        A[count] = new double[S];
    int k = 0;
    for (int i = 0; i < S; i++)
        for (int j = 0; j < S; j++) {
            A[i][j] = C[k];
            k++;
        }
    double* B = new double[S];
    B[0] = 12;
    B[1] = 13;
    B[2] = 14;
    double res = 0.93 + 0.79 + 1;
    ASSERT_NEAR(res, conj_grad(A, B, S), 0.5);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
