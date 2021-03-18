// Copyright 2021 Kryukov Sergey
#include<float.h>
#include <random>
#include <vector>
#include "../../../modules/task_1/kryukov_s_sparse_compl_mat/kryukov_s_sparse_compl_mat.h"

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
    std::vector<std::complex<double>> matC_val;
    std::vector<int> matC_colNum;
    std::vector<int> matC_rowNum;
    B = transposeMatrixGustavson(B);
    matC_rowNum.push_back(0);
    for (int rowA = 0; rowA < A.size; rowA++) {
        for (int rowB = 0; rowB < A.size; rowB++) {
            std::complex<double> scalsum = 0;
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
        matC_rowNum.push_back(matC_val.size() + matC_rowNum[rowA]);
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
