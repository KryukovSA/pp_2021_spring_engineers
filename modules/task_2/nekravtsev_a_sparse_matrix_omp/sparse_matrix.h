// Copyright 2021 Nekravtsev Alexey
#ifndef MODULES_TASK_2_NEKRAVTSEV_A_SPARSE_MATRIX_OMP_SPARSE_MATRIX_H_
#define MODULES_TASK_2_NEKRAVTSEV_A_SPARSE_MATRIX_OMP_SPARSE_MATRIX_H_

#include <vector>

struct CCS {
  int size;
  std::vector<double> value;
  std::vector<double> rows, colInd;
};

std::vector<double> GenSpareMatrix(int s);
std::vector<double> MultMatrix(int size, std::vector<double> const &A,
  std::vector<double> const &B);
CCS createCCS(int s, std::vector<double> const &mat);
CCS TranspSpareMatrix(CCS A);
CCS MultCCS(CCS A, CCS B);
CCS MultCCSParallel(CCS A, CCS B, int threads);

#endif  // MODULES_TASK_2_NEKRAVTSEV_A_SPARSE_MATRIX_OMP_SPARSE_MATRIX_H_
