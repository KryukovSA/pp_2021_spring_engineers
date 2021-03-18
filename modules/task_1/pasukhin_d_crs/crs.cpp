// Copyright 2021 Pasukhin Dmitry

#include "../../../modules/task_1/pasukhin_d_crs/crs.h"

#include <ctime>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

//=======================================================================
// function : TransformToNorm
// purpose  :
//=======================================================================

std::vector<double> TransformToNorm(const Matrix& A) {
  std::vector<double> Res(A.Lenght * A.Lenght, 0.);

  for (size_t i = 0; i < A.Lenght; ++i) {
    const size_t i1 = A.RowInd[i];
    const size_t i2 = A.RowInd[i + 1] - 1;
    for (size_t j = i1; j <= i2; j++) {
      Res[i * A.Lenght + A.Column[j]] = A.Values[j];
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
  Res.Values = std::vector<double>(VCount);

  if (lenght > 1) {
    for (size_t i = 0; i < lenght; i++) {
      for (size_t j = 0; j < ValueInRow; j++) {
        size_t my_Flag;
        do {
          Res.Column[i * ValueInRow + j] = 1 + generator() % (lenght - 1);
          my_Flag = 0;
          for (size_t k = 0; k < j; k++) {
            if (Res.Column[i * ValueInRow + j] ==
                Res.Column[i * ValueInRow + k]) {
              my_Flag = 1;
            }
          }
        } while (my_Flag == 1);
      }
      for (size_t j = 0; j < ValueInRow - 1; j++) {
        for (size_t k = 0; k < ValueInRow - 1; k++) {
          if (Res.Column[i * ValueInRow + k] >
              Res.Column[i * ValueInRow + k + 1]) {
            std::swap(Res.Column[i * ValueInRow + k],
                      Res.Column[i * ValueInRow + k + 1]);
          }
        }
      }
    }
  } else {
    Res.Column[0] = 0;
  }

  for (auto& iter : Res.Values) {
    iter = generator() % 110 + 10;
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

std::vector<double> MultNorm(const std::vector<double>& A,
                             const std::vector<double>& B,
                             const size_t lenght) {
  std::vector<double> Res(A.size());
  for (size_t i = 0; i < lenght; i++) {
    for (size_t j = 0; j < lenght; j++) {
      double sum = 0;
      for (size_t k = 0; k < lenght; k++) {
        sum += A[i * lenght + k] * B[k * lenght + j];
      }
      Res[i * lenght + j] = sum;
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
  B.Values = std::vector<double>(b.VCount);

  for (const auto& iter : b.Column) {
    B.RowInd[iter + 1]++;
  }

  size_t Index_tmp = 0;
  for (auto& iter : B.RowInd) {
    const size_t tmp = iter;
    iter = Index_tmp;
    Index_tmp = Index_tmp + tmp;
  }

  for (size_t i = 0; i < b.Lenght; i++) {
    size_t j1 = b.RowInd[i];
    size_t j2 = b.RowInd[i + 1];
    size_t Col = i;
    for (size_t j = j1; j < j2; j++) {
      double V = b.Values[j];
      size_t Row_index = b.Column[j];
      size_t IIndex = B.RowInd[Row_index + 1];
      B.Values[IIndex] = V;
      B.Column[IIndex] = Col;
      B.RowInd[Row_index + 1]++;
    }
  }

  Res.Lenght = N;
  Res.RowInd.push_back(0);
  for (size_t i = 0; i < N; i++) {
    size_t rowNZ = 0;
    for (size_t j = 0; j < N2; j++) {
      double sum = 0.0;
      for (size_t k = A.RowInd[i]; k < A.RowInd[i + 1]; k++) {
        for (size_t l = B.RowInd[j]; l < B.RowInd[j + 1]; l++) {
          if (A.Column[k] == B.Column[l]) {
            sum += A.Values[k] * B.Values[l];
            break;
          }
        }
      }

      if (fabs(sum) > std::numeric_limits<double>::epsilon()) {
        Res.Column.push_back(j);
        Res.Values.push_back(sum);
        rowNZ++;
      }
    }
    Res.RowInd.push_back(rowNZ + Res.RowInd[i]);
  }
  Res.VCount = Res.Column.size();
  return Res;
}
