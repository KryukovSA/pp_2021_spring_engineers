// Copyright 2021 Kryukov Sergey
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "./kryukov_s_sparse_compl_mat.h"

TEST(seq_version, correct_create_sparse_mat) {
    int size = 3;
    std::vector<std::complex<double>> standartMat = {
        {0, 0}, {0, 2}, {0, 0},
        {0, 1}, {0, 0}, {0, 0},
        {0, 0}, {0, 1}, {0, 0}
    };
    crs_mat sparseMat;
    sparseMat = createSparseMat(size, standartMat);
    std::vector<std::complex<double>> rightVal = { {0, 2}, {0, 1}, {0, 1} };
    std::vector<int> rightCol = { 1, 0, 1 };
    std::vector<int> rightRowNum = { 0, 1, 2, 3 };
    ASSERT_EQ(sparseMat.size, size);
    ASSERT_EQ(sparseMat.val, rightVal);
    ASSERT_EQ(sparseMat.colNum, rightCol);
    ASSERT_EQ(sparseMat.rowNum, rightRowNum);
}

TEST(seq_version, correct_transpose_mat) {
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

TEST(seq_version, correct_transpose_mat2) {
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

TEST(seq_version, check_multiplic) {
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

TEST(seq_version, check_multiplic2) {
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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
