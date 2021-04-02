// Copyright 2021 Kren Polina

#include "../../modules/task_1/kren_p_matrix/matrix.h"

#include <algorithm>
#include <vector>

std::vector<double> AdditionMatrix(const std::vector<double>& matrix1,
                                   const std::vector<double>& matrix2,
                                   const int MatrixSize) {
  int MatrixResultSize = MatrixSize * MatrixSize;
  std::vector<double> MatrixResult(MatrixResultSize);
  for (int i = 0; i < MatrixResultSize; i++) {
    MatrixResult[i] = matrix1[i] + matrix2[i];
  }
  return MatrixResult;
}

std::vector<double> SubtractionMatrix(const std::vector<double>& matrix1,
                                      const std::vector<double>& matrix2,
                                      const int MatrixSize) {
  int MatrixResultSize = MatrixSize * MatrixSize;
  std::vector<double> MatrixResult(MatrixResultSize);
  for (int i = 0; i < MatrixResultSize; i++) {
    MatrixResult[i] = matrix1[i] - matrix2[i];
  }
  return MatrixResult;
}

std::vector<double> MultiplicationMatrix(const std::vector<double>& matrix1,
                                         const std::vector<double>& matrix2,
                                         const int MatrixSize) {
  int MatrixResultSize = MatrixSize * MatrixSize;
  std::vector<double> MatrixResult(MatrixResultSize);
  for (int i = 0; i < MatrixSize; i++) {
    for (int j = 0; j < MatrixSize; j++) {
      MatrixResult[i * MatrixSize + j] = 0;
      for (int k = 0; k < MatrixSize; k++) {
        MatrixResult[i * MatrixSize + j] +=
            matrix1[i * MatrixSize + k] * matrix2[k * MatrixSize + j];
      }
    }
  }
  return MatrixResult;
}

bool CheckEqualMatrix(const std::vector<double>& matrix1,
                      const std::vector<double>& matrix2,
                      const int MatrixSize) {
  bool MatrixIsEqual = true;
  for (int i = 0; i < MatrixSize; i++)
    if (matrix1[i] != matrix2[i]) {
      MatrixIsEqual = false;
      break;
    }
  return MatrixIsEqual;
}

int CheckMatrixSize(const int MatrixSize) {
  int MatrixResultSize = 2;
  while (MatrixSize > MatrixResultSize) MatrixResultSize = MatrixResultSize * 2;
  return MatrixResultSize;
}

std::vector<double> ResizeMatrix(const std::vector<double>& matrix,
                                 const int MatrixSize) {
  int MatrixResultSize = 0;
  MatrixResultSize = CheckMatrixSize(MatrixSize);
  std::vector<double> MatrixResult(MatrixResultSize * MatrixResultSize);
  for (int i = 0; i < MatrixResultSize * MatrixResultSize; i++) {
    MatrixResult[i] = 0;
  }
  for (int i = 0; i < MatrixSize; i++) {
    for (int j = 0; j < MatrixSize; j++) {
      MatrixResult[i * MatrixResultSize + j] = matrix[i * MatrixSize + j];
    }
  }
  return MatrixResult;
}

std::vector<double> StrassenAlgorithm(const std::vector<double>& matrix1,
                                      const std::vector<double>& matrix2,
                                      int MatrixSize) {
  if (MatrixSize <= 2) {
    return MultiplicationMatrix(matrix1, matrix2, MatrixSize);
  }
  MatrixSize = MatrixSize / 2;
  int MatrixResultSize = MatrixSize * MatrixSize;

  std::vector<double> A11(MatrixResultSize);
  std::vector<double> A12(MatrixResultSize);
  std::vector<double> A21(MatrixResultSize);
  std::vector<double> A22(MatrixResultSize);
  std::vector<double> B11(MatrixResultSize);
  std::vector<double> B12(MatrixResultSize);
  std::vector<double> B21(MatrixResultSize);
  std::vector<double> B22(MatrixResultSize);

  SplitMatrixIntoPieces(matrix1, &A11, &A22, &A12, &A21, MatrixSize * 2);
  SplitMatrixIntoPieces(matrix2, &B11, &B22, &B12, &B21, MatrixSize * 2);

  std::vector<double> p1 =
      StrassenAlgorithm(AdditionMatrix(A11, A22, MatrixSize),
                        AdditionMatrix(B11, B22, MatrixSize), MatrixSize);
  std::vector<double> p2 =
      StrassenAlgorithm(AdditionMatrix(A21, A22, MatrixSize), B11, MatrixSize);
  std::vector<double> p3 = StrassenAlgorithm(
      A11, SubtractionMatrix(B12, B22, MatrixSize), MatrixSize);
  std::vector<double> p4 = StrassenAlgorithm(
      A22, SubtractionMatrix(B21, B11, MatrixSize), MatrixSize);
  std::vector<double> p5 =
      StrassenAlgorithm(AdditionMatrix(A11, A12, MatrixSize), B22, MatrixSize);
  std::vector<double> p6 =
      StrassenAlgorithm(SubtractionMatrix(A21, A11, MatrixSize),
                        AdditionMatrix(B11, B12, MatrixSize), MatrixSize);
  std::vector<double> p7 =
      StrassenAlgorithm(SubtractionMatrix(A12, A22, MatrixSize),
                        AdditionMatrix(B21, B22, MatrixSize), MatrixSize);

  std::vector<double> c11(MatrixResultSize);
  std::vector<double> c12(MatrixResultSize);
  std::vector<double> c21(MatrixResultSize);
  std::vector<double> c22(MatrixResultSize);

  c11 = AdditionMatrix(AdditionMatrix(p1, p4, MatrixSize),
                       SubtractionMatrix(p7, p5, MatrixSize), MatrixSize);
  c12 = AdditionMatrix(p3, p5, MatrixSize);
  c21 = AdditionMatrix(p2, p4, MatrixSize);
  c22 = AdditionMatrix(SubtractionMatrix(p1, p2, MatrixSize),
                       AdditionMatrix(p3, p6, MatrixSize), MatrixSize);

  return RebuildMatrix(c11, c22, c12, c21, MatrixSize);
}

void SplitMatrixIntoPieces(const std::vector<double>& matrix,
                           std::vector<double>* A11, std::vector<double>* A22,
                           std::vector<double>* A12, std::vector<double>* A21,
                           int MatrixSize) {
  int SizeOfPiece = MatrixSize / 2;
  for (int i = 0; i < SizeOfPiece; i++) {
    for (int j = 0; j < SizeOfPiece; j++) {
      A11->at(i * SizeOfPiece + j) = matrix[i * MatrixSize + j];
      A12->at(i * SizeOfPiece + j) = matrix[i * MatrixSize + j + SizeOfPiece];
      A21->at(i * SizeOfPiece + j) = matrix[(i + SizeOfPiece) * MatrixSize + j];
      A22->at(i * SizeOfPiece + j) =
          matrix[(i + SizeOfPiece) * MatrixSize + j + SizeOfPiece];
    }
  }
}

std::vector<double> RebuildMatrix(const std::vector<double>& A11,
                                  const std::vector<double>& A22,
                                  const std::vector<double>& A12,
                                  const std::vector<double>& A21,
                                  const int SizeOfPiece) {
  int MatrixResultSize = SizeOfPiece * 2;
  std::vector<double> MatrixResult(MatrixResultSize * MatrixResultSize);
  for (int i = 0; i < SizeOfPiece; i++) {
    for (int j = 0; j < SizeOfPiece; j++) {
      MatrixResult[i * MatrixResultSize + j] = A11[i * SizeOfPiece + j];
      MatrixResult[i * MatrixResultSize + j + SizeOfPiece] =
          A12[i * SizeOfPiece + j];
      MatrixResult[(i + SizeOfPiece) * MatrixResultSize + j] =
          A21[i * SizeOfPiece + j];
      MatrixResult[(i + SizeOfPiece) * MatrixResultSize + j + SizeOfPiece] =
          A22[i * SizeOfPiece + j];
    }
  }
  return MatrixResult;
}
