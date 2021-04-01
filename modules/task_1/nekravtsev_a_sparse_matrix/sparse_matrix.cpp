// Copyright 2021 Nekravtsev Alexey
#include <random>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>
#include "../../../modules/task_1/nekravtsev_a_sparse_matrix/sparse_matrix.h"

std::vector<double> GenSpareMatrix(int s) {
  std::random_device dev;
  std::mt19937 gen(dev());
  std::vector<double> temp(s * s);
  double rand = gen() % 20;

  for (int i = 0; i < s; i++) {
    for (int j = 0; j < s; j++) {
      if (rand < 10)
        temp[i * s + j] = 0;
      else
        temp[i * s + j] = gen() % 20;
      rand = gen() % 20;
    }
  }

  /*for (int i = 0; i < s; i++) {     
    for (int j = 0; j < s; j++) {
      std::cout << temp[i * s + j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;*/

  return temp;
}

std::vector<double> MultMatrix(int size, std::vector<double> const &A,
  std::vector<double> const &B) {
  std::vector<double> res = std::vector<double>(size * size, 0);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      for (int k = 0; k < size; k++)
        res[i * size + j] += A[i * size + k] * B[k * size + j];
    }
  }

  /*for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      std::cout << res[i * size + j] << " ";
    }
    std::cout << std::endl;
  }*/

  return res;
}

CCS createCCS(int s, std::vector<double> const &mat) {
  CCS res;
  res.size = s;

  for (int i = 0; i < s; i++) {
    bool f = true;
    for (int j = 0; j < s; j++) {
      if (mat[j * s + i] != 0) {
        res.value.push_back(mat[j * s + i]);
        res.rows.push_back(j);
        if (f) {
          res.colInd.push_back(res.value.size() - 1);
          f = false;
        }
      }
    }
    if (f)
      res.colInd.push_back(res.value.size());
  }
  res.colInd.push_back(res.value.size());

  /*for (int i = 0; i < res.value.size(); i++) {
    std::cout << res.value[i] << " ";
  }
  std::cout << std::endl;
  for (int i = 0; i < res.rows.size(); i++) {
    std::cout << res.rows[i] << " ";
  }
  std::cout << std::endl;
  for (int i = 0; i < res.colInd.size(); i++) {
    std::cout << res.colInd[i] << " ";
  }
  std::cout << std::endl << "-----------" << std::endl;*/

  return res;
}

CCS TranspSpareMatrix(CCS A) {
  CCS res;
  res.size = A.size;
  res.value.resize(A.value.size());
  res.rows.resize(A.rows.size());
  res.colInd = std::vector<double>(A.size + 1, 0.0);

  for (size_t i = 0; i < A.value.size(); i++) {
    res.colInd[A.rows[i] + 1]++;
  }

  double sum = 0;
  for (int i = 1; i <= A.size; i++) {
    int tmp = res.colInd[i];
    res.colInd[i] = sum;
    sum = sum + tmp;
  }

  for (int i = 0; i < A.size; i++) {
    int x = A.colInd[i];
    int y = A.colInd[i + 1];
    int col = i;
    for (int j = x; j < y; j++) {
      double V = A.value[j];
      int Rind = A.rows[j];
      int Iind = res.colInd[Rind + 1];
      res.value[Iind] = V;
      res.rows[Iind] = col;
      res.colInd[Rind + 1]++;
    }
  }
  /*
  for (int i = 0; i < res.value.size(); i++) {
    std::cout << res.value[i] << " ";
  }
  std::cout << std::endl;
  for (int i = 0; i < res.rows.size(); i++) {
    std::cout << res.rows[i] << " ";
  }
  std::cout << std::endl;
  for (int i = 0; i < res.colInd.size(); i++) {
    std::cout << res.colInd[i] << " ";
  }
  std::cout << std::endl << "-----------" << std::endl;
  */
  return res;
}

CCS MultCCS(CCS A, CCS B) {
  CCS res;
  res.size = A.size;

  res.colInd.push_back(0);
  for (int j = 0; j < A.size; j++) {
    int NZ = 0;
    for (int i = 0; i < B.size; i++) {
      double sum = 0;
      for (int n = A.colInd[i]; n < A.colInd[i + 1]; n++) {
        for (int m = B.colInd[j]; m < B.colInd[j + 1]; m++) {
          if (A.rows[n] == B.rows[m]) {
            sum += A.value[n] * B.value[m];
            break;
          }
        }
      }
      if (fabs(sum) > 0) {
        res.value.push_back(sum);
        res.rows.push_back(i);
        NZ++;
      }
    }
    res.colInd.push_back(NZ + res.colInd[j]);
  }

  /*for (int i = 0; i < res.value.size(); i++) {
    std::cout << res.value[i] << " ";
  }
  std::cout << std::endl;
  for (int i = 0; i < res.rows.size(); i++) {
    std::cout << res.rows[i] << " ";
  }
  std::cout << std::endl;
  for (int i = 0; i < res.colInd.size(); i++) {
    std::cout << res.colInd[i] << " ";
  }
  std::cout << std::endl << "-----------" << std::endl;*/

  return res;
}
