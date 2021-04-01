// Copyright 2021 Kren Polina
#include <gtest/gtest.h>

#include <iostream>
#include <vector>

#include "../../modules/task_1/kren_p_matrix/matrix.h"

TEST(StrassenAlgorithm, Test_correct_size_of_matrix) {
  int MatrixSize_1 = 64;
  int MatrixSize_2 = 50;
  int MatrixSize_3 = 30;
  int MatrixSize_4 = 14;
  ASSERT_EQ(CheckMatrixSize(MatrixSize_1), 64);
  ASSERT_EQ(CheckMatrixSize(MatrixSize_2), 64);
  ASSERT_EQ(CheckMatrixSize(MatrixSize_3), 32);
  ASSERT_EQ(CheckMatrixSize(MatrixSize_4), 16);
}

TEST(StrassenAlgorithm, Test_correct_addition_matrix) {
  int MatrixSize = 60;
  int MatrixResultSize = MatrixSize * MatrixSize;
  std::vector<double> matrix1(MatrixResultSize);
  std::vector<double> matrix2(MatrixResultSize);
  std::vector<double> matrix3(MatrixResultSize);
  std::vector<double> MatrixResult(MatrixResultSize);
  for (int i = 0; i < MatrixResultSize; i++) {
    matrix1[i] = 2 * i;
  }
  for (int i = 0; i < MatrixResultSize; i++) {
    matrix2[i] = MatrixResultSize - 2 * i;
  }
  for (int i = 0; i < MatrixResultSize; i++) {
    matrix3[i] = MatrixResultSize;
  }
  MatrixResult = AdditionMatrix(matrix1, matrix2, MatrixSize);
  ASSERT_TRUE(CheckEqualMatrix(matrix3, MatrixResult, MatrixSize));
}

TEST(StrassenAlgorithm, correct_subt) {
  int MatrixSize = 50;
  int MatrixResultSize = MatrixSize * MatrixSize;
  std::vector<double> matrix1(MatrixResultSize);
  std::vector<double> matrix2(MatrixResultSize);
  std::vector<double> matrix3(MatrixResultSize);
  std::vector<double> MatrixResult(MatrixResultSize);
  for (int i = 0; i < MatrixResultSize; i++) {
    matrix1[i] = 3 * i;
  }
  for (int i = 0; i < MatrixResultSize; i++) {
    matrix2[i] = 3 * i;
  }
  for (int i = 0; i < MatrixResultSize; i++) {
    matrix3[i] = 0;
  }
  MatrixResult = SubtractionMatrix(matrix1, matrix1, MatrixSize);
  ASSERT_TRUE(CheckEqualMatrix(matrix3, MatrixResult, MatrixSize));
}

TEST(StrassenAlgorithm, Test_correct_resize_matrix) {
  int MatrixSize = 8;
  std::vector<double> matrix1(MatrixSize * MatrixSize);
  std::vector<double> matrix2(32);
  for (int i = 0; i < MatrixSize * MatrixSize; i++) {
    matrix1[i] = i + 1;
  }
  for (int i = 0; i < 32; i++) {
    matrix2[i] = i + 1;
  }
  matrix1 = ResizeMatrix(matrix1, MatrixSize);
  ASSERT_TRUE(CheckEqualMatrix(matrix1, matrix2, MatrixSize));
}

TEST(StrassenAlgorithm, correct_split_matrix_into_pieces) {
  int MatrixSize = 4;
  int SizeOfPiece = 2;
  std::vector<double> matrix(MatrixSize * MatrixSize);
  std::vector<double> A11(SizeOfPiece * SizeOfPiece);
  std::vector<double> A12(SizeOfPiece * SizeOfPiece);
  std::vector<double> A21(SizeOfPiece * SizeOfPiece);
  std::vector<double> A22(SizeOfPiece * SizeOfPiece);
  std::vector<double> B11(SizeOfPiece * SizeOfPiece);
  std::vector<double> B12(SizeOfPiece * SizeOfPiece);
  std::vector<double> B21(SizeOfPiece * SizeOfPiece);
  std::vector<double> B22(SizeOfPiece * SizeOfPiece);

  B11[0] = 0;
  B11[1] = 1;
  B11[2] = 4;
  B11[3] = 5;

  B12[0] = 2;
  B12[1] = 3;
  B12[2] = 6;
  B12[3] = 7;

  B21[0] = 8;
  B21[1] = 9;
  B21[2] = 12;
  B21[3] = 13;

  B22[0] = 10;
  B22[1] = 11;
  B22[2] = 14;
  B22[3] = 15;

  for (int i = 0; i < MatrixSize * MatrixSize; i++) {
    matrix[i] = i;
  }
  SplitMatrixIntoPieces(matrix, &A11, &A22, &A12, &A21, MatrixSize);
  ASSERT_TRUE(CheckEqualMatrix(B11, A11, SizeOfPiece));
  ASSERT_TRUE(CheckEqualMatrix(B12, A12, SizeOfPiece));
  ASSERT_TRUE(CheckEqualMatrix(B22, A22, SizeOfPiece));
  ASSERT_TRUE(CheckEqualMatrix(B21, A21, SizeOfPiece));
}

TEST(StrassenAlgorithm, correct_strassen_16x16) {
  int MatrixSize = 16;
  int MatrixResultSize = MatrixSize * MatrixSize;
  std::vector<double> matrix1(MatrixResultSize);
  std::vector<double> matrix2(MatrixResultSize);
  std::vector<double> matrix3(MatrixResultSize);
  std::vector<double> matrix4(MatrixResultSize);
  for (int i = 0; i < MatrixResultSize; i++) {
    matrix2[i] = MatrixResultSize - i;
  }
  for (int i = 0; i < MatrixResultSize; i++) {
    matrix1[i] = i;
  }

  matrix3 = MultiplicationMatrix(matrix1, matrix2, MatrixSize);
  matrix4 = StrassenAlgorithm(matrix1, matrix2, MatrixSize);
  ASSERT_TRUE(CheckEqualMatrix(matrix3, matrix4, MatrixSize));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
