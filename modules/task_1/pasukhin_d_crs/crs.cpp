// Copyright 2021 Pasukhin Dmitry

#include "../../../modules/task_1/pasukhin_d_crs/crs.h"

#include <complex>
#include <ctime>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

//=======================================================================
// function : TransformToNorm
// purpose  :
//=======================================================================

std::vector<std::complex<double>> TransformToNorm(const Matrix& A) {
  std::vector<std::complex<double>> Res(A.Lenght * A.Lenght, 0.);

  for (size_t i = 0; i < A.Lenght; ++i) {
    const size_t i1 = A.RowInd.at(i);
    const size_t i2 = A.RowInd.at(i + 1) - 1;
    for (size_t j = i1; j <= i2; j++) {
      Res.at(i * A.Lenght + A.Column.at(j)) = A.Values.at(j);
    }
  }
  return Res;
}

//=======================================================================
// function : GenerateCRS
// purpose  :
//=======================================================================

Matrix GenerateCRS(const size_t lenght) {
  Matrix Res;
  std::mt19937 generator(static_cast<unsigned int>(time(0)));
  size_t ValueInRow = (lenght > 1) ? 1 + generator() % (lenght / 2) : 1;
  size_t VCount = ValueInRow * lenght;

  Res.Lenght = lenght;
  Res.VCount = VCount;
  Res.RowInd = std::vector<size_t>(lenght + 1);
  Res.Column = std::vector<size_t>(VCount);
  Res.Values = std::vector<std::complex<double>>(VCount);

  if (lenght > 1) {
    for (size_t i = 0; i < lenght; i++) {
      for (size_t j = 0; j < ValueInRow; j++) {
        bool isValue = false;
        do {
          isValue = false;
          Res.Column.at(i * ValueInRow + j) = 1 + generator() % (lenght - 1);
          for (size_t k = 0; k < j; k++) {
            if (Res.Column.at(i * ValueInRow + j) ==
                Res.Column.at(i * ValueInRow + k)) {
              isValue = true;
            }
          }
        } while (isValue);
      }
      for (size_t j = 0; j < ValueInRow - 1; j++) {
        for (size_t k = 0; k < ValueInRow - 1; k++) {
          if (Res.Column.at(i * ValueInRow + k) >
              Res.Column.at(i * ValueInRow + k + 1)) {
            std::swap(Res.Column.at(i * ValueInRow + k),
                      Res.Column.at(i * ValueInRow + k + 1));
          }
        }
      }
    }
  } else {
    Res.Column.at(0) = 0;
  }

  for (auto& iter : Res.Values) {
    iter = std::complex<double>(generator() % 110, generator() % 110);
  }

  size_t Count = 0;
  for (auto& iter : Res.RowInd) {
    iter = Count;
    Count += ValueInRow;
  }

  return Res;
}

//=======================================================================
// function : MultNorm
// purpose  :
//=======================================================================

std::vector<std::complex<double>> MultNorm(
    const std::vector<std::complex<double>>& A,
    const std::vector<std::complex<double>>& B, const size_t lenght) {
  std::vector<std::complex<double>> Res(A.size());
  for (size_t i = 0; i < lenght; i++) {
    for (size_t j = 0; j < lenght; j++) {
      std::complex<double> sum = 0;
      for (size_t k = 0; k < lenght; k++) {
        sum += A.at(i * lenght + k) * B.at(k * lenght + j);
      }
      Res.at(i * lenght + j) = sum;
    }
  }
  return Res;
}

//=======================================================================
// function : MultCRS
// purpose  :
//=======================================================================

Matrix MultCRS(const Matrix& A, const Matrix& b) {
  const size_t N = A.Lenght;
  const size_t N2 = b.Lenght;
  Matrix Res, B;

  B.Lenght = b.Lenght;
  B.VCount = b.VCount;
  B.Column = std::vector<size_t>(b.VCount);
  B.RowInd = std::vector<size_t>(b.Lenght + 1);
  B.Values = std::vector<std::complex<double>>(b.VCount);

  for (const auto& iter : b.Column) {
    B.RowInd.at(iter + 1)++;
  }

  size_t Index_tmp = 0;
  for (auto& iter : B.RowInd) {
    const size_t tmp = iter;
    iter = Index_tmp;
    Index_tmp = Index_tmp + tmp;
  }

  for (size_t i = 0; i < b.Lenght; i++) {
    size_t j1 = b.RowInd.at(i);
    size_t j2 = b.RowInd.at(i + 1);
    size_t Col = i;
    for (size_t j = j1; j < j2; j++) {
      std::complex<double> V = b.Values.at(j);
      size_t Row_index = b.Column.at(j);
      size_t IIndex = B.RowInd.at(Row_index + 1);
      B.Values.at(IIndex) = V;
      B.Column.at(IIndex) = Col;
      B.RowInd.at(Row_index + 1)++;
    }
  }

  Res.Lenght = N;
  Res.RowInd.push_back(0);
  for (size_t i = 0; i < N; i++) {
    size_t rowNZ = 0;
    for (size_t j = 0; j < N2; j++) {
      std::complex<double> sum = 0;
      for (size_t k = A.RowInd.at(i); k < A.RowInd.at(i + 1); k++) {
        for (size_t l = B.RowInd.at(j); l < B.RowInd.at(j + 1); l++) {
          if (A.Column.at(k) == B.Column.at(l)) {
            sum += A.Values.at(k) * B.Values.at(l);
            break;
          }
        }
      }

      if (abs(sum) > std::numeric_limits<double>::epsilon()) {
        Res.Column.push_back(j);
        Res.Values.push_back(sum);
        rowNZ++;
      }
    }
    Res.RowInd.push_back(rowNZ + Res.RowInd.at(i));
  }
  Res.VCount = Res.Column.size();
  return Res;
}
