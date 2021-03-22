// Copyright 2021 Anisimova Polina

#include <cmath>
#include <limits>
#include <random>
#include "../../../modules/task_1/anisimova_p_sparse_matrix/sparsematrix.h"

SparseMatrix::SparseMatrix(const std::vector<double>& _values,
                           const std::vector<int>& _col_indexes,
                           const std::vector<int>& _rows, int _num_nzero,
                           int _size) {
  num_nzero = static_cast<int>(_values.size());
  size = _size;
  values = _values;
  col_indexes = _col_indexes;
  rows = _rows;
}

SparseMatrix::SparseMatrix(int _size, int _num_nzero, unsigned int seed) {
  num_nzero = _num_nzero;
  size = _size;
  values.resize(num_nzero);
  rows.resize(num_nzero);
  col_indexes.resize(size + 1);
  std::mt19937 gen;
  gen.seed(seed);
  std::uniform_real_distribution<double> dbgen(0.05, 1.0);
  for (int i = 0; i < num_nzero; ++i) {
    double tmp = dbgen(gen);
    values[i] = tmp * gen();
    rows[i] = gen() % size;
    ++col_indexes[gen() % size + 1];
  }
  for (int i = 0; i < size; ++i) {
    col_indexes[i + 1] += col_indexes[i];
  }
}

bool SparseMatrix::operator==(const SparseMatrix& SM) {
  if (num_nzero != SM.num_nzero || size != SM.size) {
    return false;
  }
  return values == SM.values && col_indexes == SM.col_indexes &&
         rows == SM.rows;
}

SparseMatrix SparseMatrix::Transpose() {
  std::vector<double> tr_values(values.size());
  std::vector<int> tr_col_indexes(col_indexes.size());
  std::vector<int> tr_rows(rows.size());

  for (int i = 0; i < num_nzero; ++i) {
    ++tr_col_indexes[rows[i] + 1];
  }

  int sum = 0;
  for (int i = 1; i <= size; ++i) {
    int tmp = tr_col_indexes[i];
    tr_col_indexes[i] = sum;
    sum = sum + tmp;
  }

  for (int i = 0; i < size; ++i) {
    for (int j = col_indexes[i]; j < col_indexes[i + 1]; ++j) {
      int Iind = tr_col_indexes[rows[j] + 1];
      ++tr_col_indexes[rows[j] + 1];
      tr_values[Iind] = values[j];
      tr_rows[Iind] = i;
    }
  }
  return SparseMatrix(tr_values, tr_col_indexes, tr_rows, num_nzero, size);
}

SparseMatrix SparseMatrix::operator*(const SparseMatrix& SM) {
  std::vector<double> res_values;
  std::vector<int> res_col_indexes(size + 1);
  std::vector<int> res_rows;
  SparseMatrix M_tr = this->Transpose();

  const double eps = std::numeric_limits<double>::epsilon();

  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      double tmp = 0.0;
      for (int g = SM.col_indexes[i]; g < SM.col_indexes[i + 1]; ++g) {
        for (int f = M_tr.col_indexes[j]; f < M_tr.col_indexes[j + 1]; ++f) {
          if (SM.rows[g] == M_tr.rows[f]) {
            tmp += M_tr.values[f] * SM.values[g];
            break;
          }
        }
      }
      if (tmp > eps || tmp < -eps) {
        res_values.push_back(tmp);
        res_rows.push_back(j);
        ++res_col_indexes[i + 1];
      }
    }
    res_col_indexes[i + 1] += res_col_indexes[i];
  }
  return SparseMatrix(res_values, res_col_indexes, res_rows,
                      static_cast<int>(res_rows.size()), size);
}
