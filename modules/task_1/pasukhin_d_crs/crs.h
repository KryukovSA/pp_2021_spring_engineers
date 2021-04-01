// Copyright 2021 Pasukhin Dmitry

#ifndef MODULES_TASK_1_PASUKHIN_D_CRS_CRS_H_
#define MODULES_TASK_1_PASUKHIN_D_CRS_CRS_H_

#include <complex>
#include <vector>

//! Representation of a CRS Matrix
struct Matrix {
  std::vector<std::complex<double>>
      Values;                  //<! Array of Matrix original Value ( double )
  std::vector<size_t> Column;  //<! Array of columns number
  std::vector<size_t> RowInd;  //<! Array of rows number
  size_t Lenght = 0;           //<! Matrix size
  size_t VCount = 0;           //<! Non-zero elements count
};

//! Tool for generate a CRS Matrix
Matrix GenerateCRS(const size_t lenght);

//! Tool for sequential multilication a pair of CRS Matrixes
Matrix MultCRS(const Matrix& A, const Matrix& B);

//! Tool for transform from CRS representation to densy representation
std::vector<std::complex<double>> TransformToNorm(const Matrix& A);

//! Tool for sequential multilication a pair of densy Matrixes
std::vector<std::complex<double>> MultNorm(
    const std::vector<std::complex<double>>& A,
    const std::vector<std::complex<double>>& B, const size_t lenght);

#endif  // MODULES_TASK_1_PASUKHIN_D_CRS_CRS_H_
