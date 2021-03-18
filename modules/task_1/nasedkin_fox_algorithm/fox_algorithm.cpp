// Copyright 2021 Nasedkin Nikita
#include <random>
#include <ctime>
#include "../../../modules/task_1/nasedkin_fox_algorithm/fox_algorithm.h"

std::vector<double> MatrixInit(int size) {
  if (size <= 0) {
  throw("Incorrect size!");
  }

  std::vector<double> matrix(size*size);

  std::mt19937 random;
  random.seed(static_cast<unsigned int>(time(0)));
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      matrix[i * size + j] = random() % 100;
    }
  }
  return matrix;
}

std::vector<double> SeqMatrixCalc(std::vector<double> a,
  std::vector<double> b, int size) {
  if (a.size() != size*size) {
    throw("Incorrect size!");
  }
  std::vector<double> c(size * size, 0);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      for (int k = 0; k < size; k++) {
        c[i * size + j] += a[i * size + k] * b[k * size + j];
      }
    }
  }
  return c;
}
std::vector<double> SeqMatrixBlockCalc(std::vector<double> a,
  std::vector<double> b, int matrixSize) {
  if (matrixSize <= 0) {
    throw("Incorrect size!");
  }

  if (a.size() != matrixSize * matrixSize) {
    throw("Incorrect size!");
  }
  int blocksCount = 0;

  if (matrixSize / static_cast<int>(sqrt(procCount)) == 0) {
    blocksCount = 1;
  } else {
    blocksCount = matrixSize / static_cast<int>(sqrt(procCount));
  }

  std::vector<double> c(matrixSize * matrixSize, 0);

  for (int i = 0; i < matrixSize; i += blocksCount) {
    for (int j = 0; j < matrixSize; j += blocksCount) {
      for (int k = 0; k < matrixSize; k += blocksCount) {
        for (int i1 = 0; i1 < ((blocksCount + i)
          % matrixSize + blocksCount); i1++) {
          for (int j1 = 0; j1 < ((blocksCount + j)
            % matrixSize + blocksCount); j1++) {
            for (int k1 = 0; k1 < ((blocksCount + k)
              % matrixSize + blocksCount); k1++) {
              c[i1 * matrixSize + j1] +=
                a[i1 * matrixSize + k1] * b[k1 * matrixSize + j1];
            }
          }
        }
      }
    }
  }

  return c;
}


