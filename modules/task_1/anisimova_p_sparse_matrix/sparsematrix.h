// Copyright 2021 Anisimova Polina
#ifndef MODULES_TASK_1_ANISIMOVA_P_SPARSE_MATRIX_SPARSEMATRIX_H_
#define MODULES_TASK_1_ANISIMOVA_P_SPARSE_MATRIX_SPARSEMATRIX_H_

#include <vector>

class SparseMatrix {
 private:
  std::vector<double> values;
  std::vector<int> col_indexes, rows;
  int num_nzero, size;

 public:
  SparseMatrix(const std::vector<double>& _values,
               const std::vector<int>& _col_indexes,
               const std::vector<int>& _rows, int _num_nzero, int _size);

  SparseMatrix(int _size, int _num_nzero, unsigned int seed = 475);  // Random
  bool operator==(const SparseMatrix& SM);

  SparseMatrix Transpose();
  SparseMatrix operator*(const SparseMatrix& SM);
};

#endif  // MODULES_TASK_1_ANISIMOVA_P_SPARSE_MATRIX_SPARSEMATRIX_H_
