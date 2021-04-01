// Copyright 2021 Evseev Alexander
#include <gtest/gtest.h>
#include <vector>
#include<iostream>
#include "./evseev_a_gauss.h"

TEST(GaussFilter_Test, invalid_matrix) {
  int hight = 0;
  int widht = -1;
  ASSERT_ANY_THROW(RandMatrix(hight, widht));
}

TEST(GaussFilter_Test, Test_Rand_7x7) {
  int i = 7;
  int j = 7;
  double sigma = 7;
  int R = 2;
  Matrix gaussMat(i, std::vector<double>(j));
  Matrix mat(i, std::vector<double>(j));
  Matrix kernel = GaussKernel(R, sigma);
  mat = RandMatrix(i, j);
  gaussMat = SeqGauss(mat, i, j, R, sigma);
  printMatrix(kernel, 2 * R + 1, 2 * R + 1);
  printMatrix(mat, i, j);
  printMatrix(gaussMat, i, j);
  ASSERT_NO_THROW(RandMatrix(i, j));
}

TEST(GaussFilter_Test, Test_3x3) {
  int hight = 3;
  int widht = 3;
  double sigma = 1;
  int radius = 1;
  Matrix mat(hight, std::vector<double>(widht));
  Matrix gaussMat(hight, std::vector<double>(widht));
  Matrix resMat(hight, std::vector<double>(widht));
  Matrix KernelMat = GaussKernel(radius, sigma);
  mat[0][0] = 187;
  mat[0][1] = 234;
  mat[0][2] = 59;
  mat[1][0] = 126;
  mat[1][1] = 235;
  mat[1][2] = 215;
  mat[2][0] = 118;
  mat[2][1] = 131;
  mat[2][2] = 42;

  resMat[0][0] = 182;
  resMat[0][1] = 229;
  resMat[0][2] = 55;
  resMat[1][0] = 121;
  resMat[1][1] = 229;
  resMat[1][2] = 211;
  resMat[2][0] = 115;
  resMat[2][1] = 123;
  resMat[2][2] = 37;

  gaussMat = SeqGauss(mat, hight, widht, radius, sigma);
  printMatrix(KernelMat, 2 * radius + 1, 2 * radius + 1);
  printMatrix(mat, hight, widht);
  printMatrix(gaussMat, hight, widht);
  printMatrix(resMat, hight, widht);
  ASSERT_EQ(resMat, gaussMat);
}

TEST(GaussFilter_Test, Test_4x3) {
  int hight = 4;
  int widht = 3;
  double sigma = 1;
  int radius = 1;
  Matrix mat(hight, std::vector<double>(widht));
  Matrix gaussMat(hight, std::vector<double>(widht));
  Matrix resMat(hight, std::vector<double>(widht));
  Matrix KernelMat = GaussKernel(radius, sigma);
  mat[0][0] = 105;
  mat[0][1] = 177;
  mat[0][2] = 111;
  mat[1][0] = 200;
  mat[1][1] = 28;
  mat[1][2] = 151;
  mat[2][0] = 230;
  mat[2][1] = 44;
  mat[2][2] = 88;
  mat[3][0] = 112;
  mat[3][1] = 128;
  mat[3][2] = 155;

  resMat[0][0] = 98;
  resMat[0][1] = 170;
  resMat[0][2] = 104;
  resMat[1][0] = 194;
  resMat[1][1] = 25;
  resMat[1][2] = 146;
  resMat[2][0] = 228;
  resMat[2][1] = 38;
  resMat[2][2] = 81;
  resMat[3][0] = 109;
  resMat[3][1] = 122;
  resMat[3][2] = 147;

  gaussMat = SeqGauss(mat, hight, widht, radius, sigma);
  printMatrix(KernelMat, 2 * radius + 1, 2 * radius + 1);
  printMatrix(mat, hight, widht);
  printMatrix(gaussMat, hight, widht);
  printMatrix(resMat, hight, widht);
  ASSERT_EQ(resMat, gaussMat);
}

TEST(GaussFilter_Test, Test_8x1) {
  int hight = 8;
  int widht = 1;
  double sigma = 1;
  int radius = 1;
  Matrix mat(hight, std::vector<double>(widht));
  Matrix gaussMat(hight, std::vector<double>(widht));
  Matrix resMat(hight, std::vector<double>(widht));
  Matrix KernelMat = GaussKernel(radius, sigma);
  mat[0][0] = 21;
  mat[1][0] = 67;
  mat[2][0] = 2;
  mat[3][0] = 2;
  mat[4][0] = 77;
  mat[5][0] = 55;
  mat[6][0] = 12;
  mat[7][0] = 56;

  resMat[0][0] = 14;
  resMat[1][0] = 66;
  resMat[2][0] = 0;
  resMat[3][0] = 0;
  resMat[4][0] = 73;
  resMat[5][0] = 50;
  resMat[6][0] = 7;
  resMat[7][0] = 50;

  gaussMat = SeqGauss(mat, hight, widht, radius, sigma);
  printMatrix(KernelMat, 2 * radius + 1, 2 * radius + 1);
  printMatrix(mat, hight, widht);
  printMatrix(gaussMat, hight, widht);
  printMatrix(resMat, hight, widht);
  ASSERT_EQ(resMat, gaussMat);
}
