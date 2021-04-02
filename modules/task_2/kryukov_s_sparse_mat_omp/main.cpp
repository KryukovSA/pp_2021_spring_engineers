// Copyright 2021 Kryukov Sergey
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "./sparsemat_omp.h"

TEST(omp_version, correct_transpose_mat) {
    int size = 3;
    std::vector<std::complex<double>> standartMat = {
        {0, 0}, {0, 2}, {0, 0},
        {0, 1}, {0, 0}, {0, 0},
        {0, 0}, {0, 1}, {0, 0}
    };
    crs_mat TransponationMat, sparseMat;
    sparseMat = createSparseMat(size, standartMat);
    TransponationMat = transposeMatrixGustavson(sparseMat);
    std::vector<int> rightRowNum = { 0, 1, 3, 3 };
    ASSERT_EQ(TransponationMat.rowNum, rightRowNum);
}

TEST(omp_version, correct_transpose_mat2) {
    int size = 4;
    std::vector<std::complex<double>> standartMat = {
        {0, 0}, {0, 2}, {0, 0}, {0, 0},
        {0, 1}, {0, 0}, {0, 0}, {0, 3},
        {0, 0}, {0, 1}, {0, 0}, {0, 0},
        {0, 0}, {0, 0}, {0, 0}, {0, 0}
    };
    crs_mat TransponationMat, sparseMat;
    sparseMat = createSparseMat(size, standartMat);
    TransponationMat = transposeMatrixGustavson(sparseMat);
    std::vector<int> rightRowNum = { 0, 1, 3, 3, 4 };
    ASSERT_EQ(TransponationMat.rowNum, rightRowNum);
}

TEST(omp_version, check_multiplic) {
    int size = 2;
    std::vector<std::complex<double>> standartMat1 = {
        {0, 0}, {2, 0},
        {1, 0}, {0, 0}
    };
    std::vector<std::complex<double>> standartMat2 = {
        {0, 0}, {2, 0},
        {2, 0}, {0, 0}
    };

    crs_mat SparseMat1, SparseMat2, SparseMatResult;
    SparseMat1 = createSparseMat(size, standartMat1);
    SparseMat2 = createSparseMat(size, standartMat2);
    SparseMatResult = multiplicateMatrix(SparseMat1, SparseMat2);
    std::vector<std::complex<double>> rightVal = { {4, 0}, {2, 0} };
    ASSERT_EQ(SparseMatResult.val, rightVal);
}

TEST(omp_version, check_multiplic2) {
    int size = 2;
    std::vector<std::complex<double>> standartMat1 = {
        {0, 0}, {0, 0},
        {0, 0}, {0, 0}
    };
    std::vector<std::complex<double>> standartMat2 = {
        {0, 0}, {2, 0},
        {2, 0}, {0, 0}
    };

    crs_mat SparseMat1, SparseMat2, SparseMatResult;
    SparseMat1 = createSparseMat(size, standartMat1);
    SparseMat2 = createSparseMat(size, standartMat2);
    SparseMatResult = multiplicateMatrix(SparseMat1, SparseMat2);
    std::vector<std::complex<double>> rightVal = {};
    ASSERT_EQ(SparseMatResult.val, rightVal);
}

TEST(omp_version, check_multiplic_time) {
    int size = 500;
    double begin, end;
    crs_mat SparseMat1 = genDiagonalSparseMat(size);
    crs_mat SparseMat2 = genDiagonalSparseMat(size);
    begin = omp_get_wtime();
    crs_mat SparseMatResult = multiplicateMatrix(SparseMat1, SparseMat2);
    end = omp_get_wtime();
    std::cout << "Seq time = " << end - begin << "\n";

    begin = omp_get_wtime();
    crs_mat SparseMatResult_omp = omp_multiplicateMatrix(SparseMat1,
        SparseMat2);
    end = omp_get_wtime();
    std::cout << "OMP time = " << end - begin << "\n";

    EXPECT_EQ(SparseMatResult.val, SparseMatResult_omp.val);
    EXPECT_EQ(SparseMatResult.rowNum, SparseMatResult_omp.rowNum);
    EXPECT_EQ(SparseMatResult.colNum, SparseMatResult_omp.colNum);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
