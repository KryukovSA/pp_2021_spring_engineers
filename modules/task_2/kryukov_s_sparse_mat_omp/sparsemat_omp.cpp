// Copyright 2021 Kryukov Sergey
#include<float.h>
#include <omp.h>
#include <random>
#include <ctime>
#include <vector>
#include <string>
#include "../../../modules/task_2/kryukov_s_sparse_mat_omp/sparsemat_omp.h"

crs_mat createSparseMat(int size_,
    const std::vector<std::complex<double>> &vectMat) {
    crs_mat matrix;
    matrix.size = size_;
    matrix.rowNum.push_back(0);
    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            if (std::abs(vectMat[i*size_ + j]) < DBL_MIN)
                continue;
            matrix.val.push_back(vectMat[i*size_ + j]);
            matrix.colNum.push_back(j);
        }
        matrix.rowNum.push_back(matrix.colNum.size());
    }
    return matrix;
}

crs_mat genDiagonalSparseMat(int size_) {
    crs_mat resultMat;
    resultMat.size = size_;
    std::vector<std::complex<double>> values;
    std::vector<int> colNum, rowNum;
    rowNum.push_back(0);

    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < size_; i++) {
        values.push_back(std::complex<double>(
            static_cast<double>(gen() % 100000),
            static_cast<double>(gen() % 100000)));
        colNum.push_back(i);
        int a = i + 1;
        rowNum.push_back(a);
    }

    resultMat.val = values;
    resultMat.rowNum = rowNum;
    resultMat.colNum = colNum;

    return resultMat;
}

std::vector<std::complex<double>> MultipluValues(
    const std::vector<std::complex<double>>& first,
    const std::vector<std::complex<double>> & second,
    const int size_) {

    std::vector<std::complex<double>> resultVec;
    std::complex<double> sum = { 0.0, 0.0 };
    for (int i = 0; i < size_; i++) {
        sum = first[i] * second[i];
        resultVec.push_back(sum);
    }

    return resultVec;
}

crs_mat transposeMatrixGustavson(crs_mat matr) {
    crs_mat TrMat;
    std::vector<std::vector<std::complex<double>>> storageValue(matr.size);
    std::vector<std::vector<int>> storageCol(matr.size);
    TrMat.rowNum.push_back(0);
    for (int i = 0; i < matr.size; i++) {
        for (int j = matr.rowNum[i]; j < matr.rowNum[i + 1]; j++) {
            storageValue[matr.colNum[j]].push_back(matr.val[j]);
            storageCol[matr.colNum[j]].push_back(i);
        }
    }
    for (int i = 0; i < matr.size; i++)
        for (int j = 0; j < static_cast<int>(storageCol[i].size()); j++) {
            TrMat.colNum.push_back(storageCol[i][j]);
            TrMat.val.push_back(storageValue[i][j]);
        }
    int sum = 0;
    for (int i = 0; i < matr.size; i++) {
        sum += static_cast<int>(storageCol[i].size());
        TrMat.rowNum.push_back(sum);
    }
    return TrMat;
}

crs_mat multiplicateMatrix(crs_mat A, crs_mat B) {
    crs_mat C;
    if (A.size != B.size)
        throw(std::string)"incorrect size";
    C.size = A.size;
    std::vector<std::complex<double>> matC_val;
    std::vector<int> matC_colNum;
    std::vector<int> matC_rowNum;
    B = transposeMatrixGustavson(B);
    matC_rowNum.push_back(0);
    for (int rowA = 0; rowA < A.size; rowA++) {
        for (int rowB = 0; rowB < A.size; rowB++) {
            std::complex<double> scalsum = { 0.0, 0.0 };
            for (int k = A.rowNum[rowA]; k < A.rowNum[rowA + 1]; k++) {
                for (int n = B.rowNum[rowB]; n < B.rowNum[rowB + 1]; n++) {
                    if (A.colNum[k] == B.colNum[n]) {
                        scalsum += A.val[k] * B.val[n];
                        break;
                    }
                }
            }
            if (std::abs(scalsum) >= DBL_MIN) {
                matC_val.push_back(scalsum);
                matC_colNum.push_back(rowB);
            }
        }
        matC_rowNum.push_back(matC_val.size());
    }
    for (int j = 0; j < static_cast<int>(matC_colNum.size()); j++) {
        C.colNum.push_back(matC_colNum[j]);
        C.val.push_back(matC_val[j]);
    }
    for (int i = 0; i <= A.size; i++) {
        C.rowNum.push_back(matC_rowNum[i]);
    }
    return C;
}

crs_mat omp_multiplicateMatrix(crs_mat A, crs_mat B) {
    crs_mat C;
    if (A.size != B.size)
        throw(std::string)"incorrect size";
    C.size = A.size;
    std::vector<std::vector<std::complex<double>>> matC_val(A.size);
    std::vector<std::vector<int>> matC_colNum(A.size);
    std::vector<int> matC_rowNum;
    B = transposeMatrixGustavson(B);
    matC_rowNum.push_back(0);
    int n, j;

    #pragma omp parallel
    {
        std::vector<int> tmp(C.size, -1);
        #pragma omp for private(j, n) schedule(static)
        for (int rowA = 0; rowA < A.size; rowA++) {
            tmp.assign(A.size, -1);
            int indexfirst = A.rowNum[rowA];
            int indexSecond = A.rowNum[rowA + 1];

            for (j = indexfirst; j < indexSecond; j++) {
                int column = A.colNum[j];
                tmp[column] = j;
            }

            for (j = 0; j < A.size; j++) {
                std::complex<double> scalsum = { 0.0, 0.0 };
                for (n = B.rowNum[j]; n < B.rowNum[j + 1]; n++) {
                    if (tmp[B.colNum[n]] != -1) {
                        scalsum += A.val[tmp[B.colNum[n]]] * B.val[n];
                    }
                }

                if (std::abs(scalsum) >= DBL_MIN) {
                    matC_val[rowA].push_back(scalsum);
                    matC_colNum[rowA].push_back(j);
                }
            }
        }
    }

    for (int j = 0; j < static_cast<int>(A.size); j++) {
        for (int i = 0; i < static_cast<int>(matC_colNum[j].size()); i++) {
            C.colNum.push_back(matC_colNum[j][i]);
            C.val.push_back(matC_val[j][i]);
        }
        matC_rowNum.push_back(C.val.size());
    }
    for (int i = 0; i <= A.size; i++) {
        C.rowNum.push_back(matC_rowNum[i]);
    }
    return C;
}
