// Copyright 2021 Kryukov Sergey
#include <random>
#include <vector>
#include "../../../modules/task_1/kryukov_s_sparse_compl_mat/kryukov_s_sparse_compl_mat.h"
#include<float.h>


void createSparseMat(int size_, const std::vector<std::complex<double>> &vectMat, crs_mat &matrix) {
	matrix.size = size_;
	matrix.rowNum.push_back(0);
	for (int i = 0; i < size_; i++) {
		for (int j = 0; j < size_; j++) {
			if (std::abs(vectMat[i*size_ + j]) < DBL_MIN)
				continue;
			matrix.val.push_back(vectMat[i*size_ + j]);
			matrix.colNum.push_back(j);
		}
		matrix.rowNum.push_back(matrix.colNum.size());
	}
}

void transposeMatrix(crs_mat matr, crs_mat &TrMat) {

}