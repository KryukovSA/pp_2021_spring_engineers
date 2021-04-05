// Copyright 2021 Kryukov Sergey
#ifndef MODULES_TASK_3_KRYUKOV_S_SPARSE_MAT_TBB_SPARSEMAT_TBB_H_
#define MODULES_TASK_3_KRYUKOV_S_SPARSE_MAT_TBB_SPARSEMAT_TBB_H_

#include <tbb/tbb.h>
#include <vector>
#include <complex>
#include "tbb/task_scheduler_init.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"


struct crs_mat {
    int size;
    std::vector<std::complex<double>> val;
    std::vector<int> colNum, rowNum;
};
crs_mat createSparseMat(int size_,
    const std::vector<std::complex<double>> &vectMat);

crs_mat genDiagonalSparseMat(int size_);
std::vector<std::complex<double>> MultipluValues(
    const std::vector<std::complex<double>> & first,
    const std::vector<std::complex<double>> & second, const int size_);

crs_mat transposeMatrixGustavson(crs_mat matr);
crs_mat multiplicateMatrix(crs_mat A, crs_mat B);
crs_mat multiplicateMatrixTBB(crs_mat A, crs_mat B);
#endif  // MODULES_TASK_3_KRYUKOV_S_SPARSE_MAT_TBB_SPARSEMAT_TBB_H_
