// Copyright 2021 Zlobin George
#include "../../../modules/task_1/zlobin_g_sparse_matrix_ccs_mult_complex/matrix_ccs_mult.h"
#include <random>
#include <algorithm>

MatrixCCS::MatrixCCS(int nCollumns, int nRows, int nNotZero) {
    if (nCollumns <= 0 || nRows <= 0) {
        throw "Incorrect matrix size";
    } else if (nNotZero < 0 || nNotZero > nCollumns * nRows) {
        throw "Incorrect number of not zero elements";
    }

    _nCollumns = nCollumns;
    _nRows = nRows;
    _nNotZero = nNotZero;

    _collumnsIndexes.reserve(_nCollumns + 1);
    _rows.reserve(_nRows);
    _values.reserve(_nNotZero);
}

MatrixCCS::MatrixCCS(int nCollumns, int nRows,
                     std::vector<std::complex<int>> matrix) {
    if (nCollumns <= 0 || nRows <= 0) {
        throw "Incorrect matrix size";
    } else if (static_cast<int>(matrix.size()) != nCollumns * nRows) {
        throw "Size of matrix doesn't match given parameters";
    }

    _nCollumns = nCollumns;
    _nRows = nRows;

    _collumnsIndexes.reserve(_nCollumns + 1);
    _rows.reserve(_nRows);

    _collumnsIndexes.push_back(0);
    for (int j = 0; j < _nCollumns; j++) {
        for (int i = 0; i < _nRows; i++) {
            if (matrix[i * _nCollumns + j] != std::complex<int>(0, 0)) {
                _values.push_back(matrix[i * _nCollumns + j]);
                _rows.push_back(i);
            }
        }
        _collumnsIndexes.push_back(static_cast<int>(_values.size()));
    }

    _nNotZero = _collumnsIndexes[_nCollumns];
}

MatrixCCS::MatrixCCS(int nCollumns, int nRows,
                     std::vector<int> collumnsIndexes,
                     std::vector<int> rows,
                     std::vector<std::complex<int>> values) {
    if (nCollumns <= 0 || nRows <= 0) {
        throw "Incorrect matrix size";
    } else if (static_cast<int>(values.size()) > nCollumns * nRows) {
        throw "More elements when possible";
    } else if (static_cast<int>(collumnsIndexes.size()) != nCollumns + 1) {
        throw "Incorrect collumns indexes";
    } else if (std::find_if(rows.begin(), rows.end(),
               [&nRows](int i) { return i >= nRows; }) != rows.end()) {
        throw "Incorrect rows";
    }

    _nCollumns = nCollumns;
    _nRows = nRows;
    _nNotZero = static_cast<int>(values.size());
    _collumnsIndexes = collumnsIndexes;
    _rows = rows;
    _values = values;
}

MatrixCCS MatrixCCS::Transpose() {
    MatrixCCS transposed{_nRows, _nCollumns, _nNotZero};

    transposed._collumnsIndexes.resize(_nRows + 1);
    for (int i = 0; i < _nNotZero; i++) {
        transposed._collumnsIndexes[_rows[i] + 1]++;
    }

    int tmp, sum = 0;
    for (int i = 1; i <= _nRows; i++) {
        tmp = transposed._collumnsIndexes[i];
        transposed._collumnsIndexes[i] = sum;
        sum += tmp;
    }

    transposed._rows.resize(_nNotZero);
    transposed._values.resize(_nNotZero);

    int j1, j2;
    int row, column, place;
    std::complex<int> value;
    for (int i = 0; i < _nCollumns; i++) {
        j1 = _collumnsIndexes[i];
        j2 = _collumnsIndexes[i + 1];
        row = i;
        for (int j = j1; j < j2; j++) {
            value = _values[j];
            column = _rows[j];
            place = transposed._collumnsIndexes[column + 1];
            transposed._rows[place] = row;
            transposed._values[place] = value;
            transposed._collumnsIndexes[column + 1]++;
        }
    }

    return transposed;
}

MatrixCCS MatrixCCS::operator*(const MatrixCCS& B) {
    if (_nCollumns != B._nRows) {
        throw "Can't multiply matrix which not corresponding";
    }

    MatrixCCS AT = Transpose();
    MatrixCCS product{B._nCollumns, _nRows, 0};

    int columnNotZero;
    std::complex<int> value;

    product._collumnsIndexes.push_back(0);
    for (int i = 0; i < B._nCollumns; i++) {
        columnNotZero = 0;
        for (int j = 0; j < AT._nCollumns; j++) {
            value = 0;

            // Scalar collumns multiplication
            for (int k = B._collumnsIndexes[i];
                 k < B._collumnsIndexes[i + 1]; k++) {
                for (int l = AT._collumnsIndexes[j];
                     l < AT._collumnsIndexes[j + 1]; l++) {
                    if (B._rows[k] == AT._rows[l]) {
                        value += B._values[k] * AT._values[l];
                        break;
                    }
                }
            }

            if (value != std::complex<int>(0, 0)) {
                product._values.push_back(value);
                product._rows.push_back(j);
                columnNotZero++;
            }
        }
        product._collumnsIndexes.push_back(product._collumnsIndexes[i] +
                                           columnNotZero);
    }

    product._nNotZero = static_cast<int>(product._values.size());
    return product;
}

void MatrixCCS::FillRandom(unsigned seed, int min, int max) {
    _collumnsIndexes.clear();
    _rows.clear();
    _values.clear();

    std::mt19937 random;
    random.seed(seed);

    std::complex<int> value;
    const double probBarrier = 1.0 * _nNotZero / (_nCollumns * _nRows);

    std::uniform_real_distribution<> probDistrib(0.0, 1.0);
    std::uniform_int_distribution<int> valueDistrib(min, max);

    _collumnsIndexes.push_back(0);
    for (int collumn = 0; collumn < _nCollumns; collumn++) {
        for (int row = 0; row < _nRows; row++) {
            if (static_cast<int>(_values.size()) == _nNotZero) {
                break;
            } else if (_nNotZero - static_cast<int>(_values.size()) + collumn * _nRows + row ==
                       _nCollumns * _nRows ||
                       (static_cast<int>(_values.size()) < _nNotZero &&
                        probDistrib(random) < probBarrier)) {
                do {
                    value = std::complex<int>(valueDistrib(random), valueDistrib(random));
                } while (value == std::complex<int>(0, 0));
                _values.push_back(value);
                _rows.push_back(row);
            }
        }
        _collumnsIndexes.push_back(static_cast<int>(_values.size()));
        if (static_cast<int>(_values.size()) == _nNotZero) {
            break;
        }
    }
}

// void MatrixCCS::Print() {
//     for (int i = 0; i < _nCollumns; i++) {
//         for (int k = _collumnsIndexes[i];
//                 k < _collumnsIndexes[i + 1]; k++) {
//             std::cout << "Column " << i << "\tRow " << _rows[k] <<
//                 "\tValueR" << _values[k].real() << "\tValueI" << _values[k].imag() << "\n";
//         }
//     }
// }

bool operator==(const MatrixCCS& A, const MatrixCCS& B) {
    return A._nCollumns == B._nCollumns &&
           A._nRows == B._nRows &&
           A._nNotZero == B._nNotZero &&
           A._collumnsIndexes == B._collumnsIndexes &&
           A._rows == B._rows &&
           A._values == B._values;
}
