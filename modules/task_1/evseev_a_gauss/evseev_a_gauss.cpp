// Copyright 2021 Evseev Alexander
#include <vector>
#include <random>
#include <ctime>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include "../../../modules/task_1/evseev_a_gauss/evseev_a_gauss.h"


int clamp(int value, int max, int min) {
  if (value < min) {
    return min;
  }
  if (value > max) {
    return max;
  }
  return value;
}
Matrix RandMatrix(int hight, int widht) {
  if ((hight <= 0) || (widht <= 0))
    throw std::invalid_argument("Invalid size");
  std::mt19937 gen;
  gen.seed(static_cast<int>(time(0)));
  Matrix matrix(hight, std::vector<double>(widht));
  for (int i = 0; i < hight; i++) {
    for (int j = 0; j < widht; j++) {
      matrix[i][j] = gen() % 100;
    }
  }
  return matrix;
}

Matrix GaussKernel(int R, double sigma) {
  const int size = 2 * R + 1;
  double norm = 0;
  Matrix kernel(size, std::vector<double>(size));
  for (int i = -R; i <= R; i++) {
    for (int j = -R; j <= R; j++) {
      kernel[i + R][j + R] =
          static_cast<double> (exp(-(i * i + j * j) / (sigma * sigma)));
      norm = norm + kernel[i + R][j + R];
    }
  }
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      kernel[i][j] = kernel[i][j] / norm;
    }
  }
  return kernel;
}

Matrix SeqGauss(Matrix mat, int hight, int widht, int R,
                            double sigma) {
  Matrix finMat(hight, std::vector<double>(widht));
  Matrix kernel = GaussKernel(R, sigma);
  for (int x = 0; x < hight; x++) {
    for (int y = 0; y < widht; y++) {
      int finValue = 0;
      for (int i = -R; i <= R; i++) {
        for (int j = -R; j <= R; j++) {
          double value = mat[x][y];
          finValue += value * kernel[i + R][j + R];
        }
      }
      finValue = clamp(finValue, 255, 0);
      finMat[x][y] = finValue;
    }
  }
  return finMat;
}

void printMatrix(Matrix mat, int hight, int widht) {
  std::cout << "Matrix:" << std::endl;
  for (int i = 0; i < hight; i++) {
    for (int j = 0; j < widht; j++) {
      std::cout << mat[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
