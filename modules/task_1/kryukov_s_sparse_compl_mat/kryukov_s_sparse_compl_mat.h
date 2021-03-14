// Copyright 2021 Kryukov Sergey
#ifndef MODULES_TASK_1_KRYUKOV_S_SPARSE_COMPL_MAT_KRYUKOV_S_SPARSE_COMPL_MAT_H_
#define MODULES_TASK_1_KRYUKOV_S_SPARSE_COMPL_MAT_KRYUKOV_S_SPARSE_COMPL_MAT_H_
//функцию умножения двух разреженных матриц

#include <vector>
#include <complex>

struct crs_mat {
	int size;
	std::vector<std::complex<double>> val;
	std::vector<int> colNum, rowNum;
};
void createSparseMat(int size_, const std::vector<std::complex<double>> & vectMat, crs_mat &matrix);
void transposeMatrix(crs_mat matr, crs_mat &TrMat);

#endif  // MODULES_TASK_1_KRYUKOV_S_SPARSE_COMPL_MAT_KRYUKOV_S_SPARSE_COMPL_MAT_H_