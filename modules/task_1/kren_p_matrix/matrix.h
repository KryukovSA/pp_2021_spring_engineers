// Copyright 2021 Kren Polina
#ifndef MODULES_TASK_1_KREN_P_MATRIX_MATRIX_H_
#define MODULES_TASK_1_KREN_P_MATRIX_MATRIX_H_

#include <random>
#include <vector>

std::vector<double> AdditionMatrix(const std::vector<double>& matrix1,
                                   const std::vector<double>& matrix2,
                                   const int MatrixSize);

std::vector<double> SubtractionMatrix(const std::vector<double>& matrix1,
                                      const std::vector<double>& matrix2,
                                      const int MatrixSize);

std::vector<double> MultiplicationMatrix(const std::vector<double>& matrix1,
                                         const std::vector<double>& matrix2,
                                         const int MatrixSize);

bool CheckEqualMatrix(const std::vector<double>& matrix1,
                      const std::vector<double>& matrix2, const int MatrixSize);

int CheckMatrixSize(const int MatrixSize);

std::vector<double> ResizeMatrix(const std::vector<double>& matrix,
                                 const int MatrixSize);

std::vector<double> StrassenAlgorithm(const std::vector<double>& matrix1,
                                      const std::vector<double>& matrix2,
                                      int MatrixSize);

void SplitMatrixIntoPieces(const std::vector<double>& matrix,
                           std::vector<double>* A11, std::vector<double>* A22,
                           std::vector<double>* A12, std::vector<double>* A21,
                           int MatrixSize);

std::vector<double> RebuildMatrix(const std::vector<double>& A11,
                                  const std::vector<double>& A22,
                                  const std::vector<double>& A12,
                                  const std::vector<double>& A21,
                                  const int SizeOfPiece);

#endif  // MODULES_TASK_1_KREN_P_MATRIX_MATRIX_H_
