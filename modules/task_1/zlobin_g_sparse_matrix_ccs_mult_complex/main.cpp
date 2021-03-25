// Copyright 2021 Zlobin George
#include <gtest/gtest.h>
#include "./matrix_ccs_mult.h"

// Tests for Constructor MatrixCCS(int nCollumns, int nRows, int nNotZero);
TEST(MatrixCCSConstructorFromNCollumnsNRowsNNotZero, ThrowIfIncorrectNCollumns1) {
    ASSERT_ANY_THROW(MatrixCCS(-10, 10, 3));
}

TEST(MatrixCCSConstructorFromNCollumnsNRowsNNotZero, ThrowIfIncorrectNRows1) {
    ASSERT_ANY_THROW(MatrixCCS(10, 0, 3));
}

TEST(MatrixCCSConstructorFromNCollumnsNRowsNNotZero, ThrowIfIncorrectNNotZero) {
    ASSERT_ANY_THROW(MatrixCCS(10, 10, -3));
}

TEST(MatrixCCSConstructorFromNCollumnsNRowsNNotZero, ThrowIfNNotZeroMoreThanAvailable) {
    ASSERT_ANY_THROW(MatrixCCS(10, 10, 101));
}

TEST(MatrixCCSConstructorFromNCollumnsNRowsNNotZero, NoThrowWithCorrectParameters1) {
    ASSERT_NO_THROW(MatrixCCS(10, 10, 3));
}

TEST(MatrixCCSConstructorFromNCollumnsNRowsNNotZero, CanCreateMatrixWithZeroElements1) {
    ASSERT_NO_THROW(MatrixCCS(10, 10, 0));
}

// Tests for Constructor MatrixCCS(nCollumns, nRows, matrix);
TEST(MatrixCCSConstructorFromNCollumnsNRowsMatrix, ThrowIfIncorrectNCollumns2) {
    ASSERT_ANY_THROW(MatrixCCS(0, 2,
        { {2, 3}, {0, 0},
        {0, -1}, {-7, 0} }));
}

TEST(MatrixCCSConstructorFromNCollumnsNRowsMatrix, ThrowIfIncorrectNRows2) {
    ASSERT_ANY_THROW(MatrixCCS(2, -3,
        { {0, 0}, {2, 3},
        {0, -1}, {-7, 0} }));
}

TEST(MatrixCCSConstructorFromNCollumnsNRowsMatrix, ThrowIfMatrixHasIncorrectSize) {
    ASSERT_ANY_THROW(MatrixCCS(2, 2,
        { {0, 0}, {2, 3}, {7, 0},
        {0, -1}, {-7, 0}, {0, 0},
        {0, 0}, {0, 0}, {-3, 10} }));
}

TEST(MatrixCCSConstructorFromNCollumnsNRowsMatrix, NoThrowWithCorrectParameters2) {
    ASSERT_NO_THROW(MatrixCCS(3, 3,
        { {0, 0}, {2, 3}, {7, 0},
        {0, -1}, {-7, 0}, {0, 0},
        {0, 0}, {0, 0}, {-3, 10} }));
}

TEST(MatrixCCSConstructorFromNCollumnsNRowsMatrix, CanCreateMatrixWithZeroElements2) {
    ASSERT_NO_THROW(MatrixCCS(3, 3,
        { {0, 0}, {0, 0}, {0, 0},
        {0, 0}, {0, 0}, {0, 0},
        {0, 0}, {0, 0}, {0, 0} }));
}

// Tests for Constructor MatrixCCS(int nCollumns, int nRows,
//                                 std::vector<int> collumnsIndexes,
//                                 std::vector<int> rows,
//                                 std::vector<std::complex<int>> values);
TEST(MatrixCCSConstructorFromDirectGivenFields, ThrowIfIncorrectNCollumns3) {
    ASSERT_ANY_THROW(MatrixCCS(-2, 2,
        { 0, 0, 2 },
        { 0, 1 },
        { {-7, 0}, {0, -10} }));
}

TEST(MatrixCCSConstructorFromDirectGivenFields, ThrowIfIncorrectNRows3) {
    ASSERT_ANY_THROW(MatrixCCS(2, 0,
        { 0, 0, 2 },
        { 0, 1 },
        { {-7, 0}, {0, -10} }));
}

TEST(MatrixCCSConstructorFromDirectGivenFields, ThrowIfGivenMoreValuesThanMatrixSize) {
    ASSERT_ANY_THROW(MatrixCCS(2, 0,
        { 0, 0, 2 },
        { 0, 1 },
        { {-7, 0}, {0, -10} }));
}

TEST(MatrixCCSConstructorFromDirectGivenFields, ThrowIfIncorrectCollumnsIndexes) {
    ASSERT_ANY_THROW(MatrixCCS(2, 2,
        { 0, 0, 2, 2 },
        { 0, 1 },
        { {-7, 0}, {0, -10} }));
}

TEST(MatrixCCSConstructorFromDirectGivenFields, ThrowIfRowsHasIncorrectValue) {
    ASSERT_ANY_THROW(MatrixCCS(2, 2,
        { 0, 0, 2 },
        { 0, 2 },
        { {-7, 0}, {0, -10} }));
}

TEST(MatrixCCSConstructorFromDirectGivenFields, NoThrowWithCorrectParameters3) {
    ASSERT_NO_THROW(MatrixCCS(2, 2,
        { 0, 0, 2 },
        { 0, 1 },
        { {-7, 0}, {0, -10} }));
}

TEST(MatrixCCSConstructorFromDirectGivenFields, CanCreateMatrixWithZeroElements3) {
    ASSERT_NO_THROW(MatrixCCS(2, 2,
        { 0, 0, 0},
        {},
        {}));
}

// Tests for constructors MatrixCCS are equivalent
TEST(MatrixCCSConstructorAreEquivalent, MatrixWithZeroElements) {
    EXPECT_EQ(MatrixCCS(3, 3,
        { {0, 0}, {0, 0}, {0, 0},
        {0, 0}, {0, 0}, {0, 0},
        {0, 0}, {0, 0}, {0, 0} }),
              MatrixCCS(3, 3,
        { 0, 0, 0, 0},
        {},
        {}));
}

TEST(MatrixCCSConstructorAreEquivalent, SquareMatrix1) {
    EXPECT_EQ(MatrixCCS(3, 3,
        { {0, 0}, {2, 3}, {7, 0},
        {0, -1}, {-7, 0}, {0, 0},
        {0, 0}, {0, 0}, {-3, 10} }),
              MatrixCCS(3, 3,
        { 0, 1, 3, 5 },
        { 1, 0, 1, 0, 2 },
        { {0, -1}, {2, 3}, {-7, 0},
        {7, 0}, {-3, 10} }));
}

TEST(MatrixCCSConstructorAreEquivalent, Row1) {
    EXPECT_EQ(MatrixCCS(3, 1,
        { {0, 0}, {2, 3}, {7, 0} }),
              MatrixCCS(3, 1,
        { 0, 0, 1, 2 },
        { 0, 0 },
        { {2, 3}, {7, 0} }));
}

TEST(MatrixCCSConstructorAreEquivalent, Collumn) {
    EXPECT_EQ(MatrixCCS(1, 3,
        { {0, 0},
        {0, -1},
        {0, 0} }),
              MatrixCCS(1, 3,
        { 0, 1 },
        { 1 },
        { {0, -1} }));
}

TEST(MatrixCCSConstructorAreEquivalent, NotSquareMatrix1) {
    EXPECT_EQ(MatrixCCS(3, 2,
        { {0, 0}, {2, 3}, {7, 0},
        {0, -1}, {-7, 0}, {0, 0} }),
              MatrixCCS(3, 2,
        { 0, 1, 3, 4 },
        { 1, 0, 1, 0 },
        { {0, -1}, {2, 3}, {-7, 0},
        {7, 0} }));
}

TEST(MatrixCCSConstructorAreEquivalent, DifferentSizesNotSame) {
    EXPECT_FALSE(MatrixCCS(3, 3,
        { {0, 0}, {2, 3}, {7, 0},
        {0, -1}, {-7, 0}, {0, 0},
        {0, 0}, {0, 0}, {-3, 10} }) ==
              MatrixCCS(3, 2,
        { 0, 1, 3, 4 },
        { 1, 0, 1, 0 },
        { {0, -1}, {2, 3}, {-7, 0},
        {7, 0} }));
}

TEST(MatrixCCSConstructorAreEquivalent, DifferentValuesNotSame) {
    EXPECT_FALSE(MatrixCCS(3, 3,
        { {0, 0}, {2, 3}, {7, 0},
        {0, -1}, {7, 0}, {0, 0},
        {0, 0}, {0, 0}, {-3, 10} }) ==
              MatrixCCS(3, 3,
        { 0, 1, 3, 5 },
        { 1, 0, 1, 0, 2 },
        { {0, -1}, {2, 3}, {-7, 0},
        {7, 0}, {-3, 10} }));
}

// Tests for FillRandom(unsigned seed = 132, int min = -1000, int max = 1000);
TEST(MatrixCCSFillWithRandomValues, CanFillMatrix) {
    MatrixCCS A = MatrixCCS(3, 3, 0);
    ASSERT_NO_THROW(A.FillRandom());
}

TEST(MatrixCCSFillWithRandomValues, SameSeedSameMatrix) {
    MatrixCCS A = MatrixCCS(3, 3, 0);
    MatrixCCS B = A;
    A.FillRandom();
    B.FillRandom();
    EXPECT_EQ(A, B);
}

// Tests for Transpose()
TEST(MatrixCCSTranspose, CanTranspose) {
    MatrixCCS A = MatrixCCS(3, 3,
        { {0, 0}, {2, 3}, {7, 0},
        {0, -1}, {-7, 0}, {0, 0},
        {0, 0}, {0, 0}, {-3, 10} });
    ASSERT_NO_THROW(A.Transpose());
}

TEST(MatrixCCSTranspose, SquareMatrix2) {
    MatrixCCS A = MatrixCCS(3, 3,
        { {0, 0}, {2, 3}, {7, 0},
        {0, -1}, {-7, 0}, {0, 0},
        {0, 0}, {0, 0}, {-3, 10} });
    MatrixCCS AT = A.Transpose();
    MatrixCCS ATref = MatrixCCS(3, 3,
        { {0, 0}, {0, -1}, {0, 0},
        {2, 3}, {-7, 0}, {0, 0},
        {7, 0}, {0, 0}, {-3, 10} });
    EXPECT_EQ(ATref, AT);
    EXPECT_EQ(A, AT.Transpose());
}

TEST(MatrixCCSTranspose, Row2) {
    MatrixCCS A = MatrixCCS(3, 1,
        { {0, 0}, {2, 3}, {7, 0} });
    MatrixCCS AT = A.Transpose();
    MatrixCCS ATref = MatrixCCS(1, 3,
        { {0, 0},
        {2, 3},
        {7, 0} });
    EXPECT_EQ(ATref, AT);
    EXPECT_EQ(A, AT.Transpose());
}

TEST(MatrixCCSTranspose, NotSquareMatrix2) {
    MatrixCCS A = MatrixCCS(3, 2,
        { {0, 0}, {2, 3}, {7, 0},
        {0, -1}, {-7, 0}, {0, 0} });
    MatrixCCS AT = A.Transpose();
    MatrixCCS ATref = MatrixCCS(2, 3,
        { {0, 0}, {0, -1},
        {2, 3}, {-7, 0},
        {7, 0}, {0, 0} });
    EXPECT_EQ(ATref, AT);
    EXPECT_EQ(A, AT.Transpose());
}

// Tests for Multiplication
TEST(MatrixCCSMultiplication, ThrowIfNotCorrespondingMatrices) {
    MatrixCCS A = MatrixCCS(3, 2,
        { {0, 0}, {2, 3}, {7, 0},
        {0, -1}, {-7, 0}, {0, 0} });
    MatrixCCS B = MatrixCCS(2, 4,
        { {0, 0}, {0, -1},
        {2, 3}, {-7, 0},
        {7, 0}, {0, 0},
        {0, -10}, {20, 0} });
    ASSERT_ANY_THROW(A * B);
}

TEST(MatrixCCSMultiplication, CanMultiplyCorrespondingMatrices) {
    MatrixCCS A = MatrixCCS(3, 2,
        { {0, 0}, {2, 3}, {7, 0},
        {0, -1}, {-7, 0}, {0, 0} });
    MatrixCCS B = MatrixCCS(2, 3,
        { {0, 0}, {0, -1},
        {2, 3}, {-7, 0},
        {7, 0}, {0, 0} });
    ASSERT_NO_THROW(A * B);
}

TEST(MatrixCCSMultiplication, MyltiplyNumbers) {
    MatrixCCS A = MatrixCCS(1, 1,
        { {20, -30} });
    MatrixCCS B = MatrixCCS(1, 1,
        { {86, 360} });
    MatrixCCS AB = MatrixCCS(1, 1,
        { {12520, 4620} });
    ASSERT_EQ(AB, A * B);
}

TEST(MatrixCCSMultiplication, MyltiplyOnZeroMatrix) {
    MatrixCCS A = MatrixCCS(3, 2,
        { {0, 0}, {20, 0}, {7, 0},
        {8, 0}, {-7, 0}, {0, 0} });
    MatrixCCS B = MatrixCCS(2, 3,
        { {0, 0}, {0, 0},
        {0, 0}, {0, 0},
        {0, 0}, {0, 0} });
    MatrixCCS AB = MatrixCCS(2, 2,
        { {0, 0}, {0, 0},
        {0, 0}, {0, 0} });
    ASSERT_EQ(AB, A * B);
}

TEST(MatrixCCSMultiplication, MyltiplyOnSingularMatrix) {
    MatrixCCS A = MatrixCCS(2, 2,
        { {1, 0}, {0, 0},
        {0, 0}, {1, 0} });
    MatrixCCS B = MatrixCCS(2, 2,
        { {3, 20}, {4, 0},
        {0, -3}, {0, 0} });
    ASSERT_EQ(B, A * B);
}

TEST(MatrixCCSMultiplication, MatrixMultiplicationExample1) {
    MatrixCCS A = MatrixCCS(3, 2,
        { {0, 0}, {20, 0}, {7, 0},
        {8, 0}, {-7, 0}, {0, 0} });
    MatrixCCS B = MatrixCCS(2, 3,
        { {0, 0}, {0, 0},
        {4, 0}, {-7, 0},
        {0, 0}, {0, 0} });
    MatrixCCS AB = MatrixCCS(2, 2,
        { {80, 0}, {-140, 0},
        {-28, 0}, {49, 0} });
    ASSERT_EQ(AB, A * B);
}

TEST(MatrixCCSMultiplication, MatrixMultiplicationExample2) {
    MatrixCCS A = MatrixCCS(3, 4,
        { {0, 0}, {0, 0}, {0, 0},
        {0, 0}, {-7, 0}, {0, 0},
        {0, 0}, {0, 0}, {4, 7},
        {4, -3}, {0, 0}, {0, 0} });
    MatrixCCS B = MatrixCCS(2, 3,
        { {0, -3}, {0, 0},
        {0, 0}, {0, 0},
        {0, 0}, {7, -10} });
    MatrixCCS AB = MatrixCCS(2, 4,
        { {0, 0}, {0, 0},
        {0, 0}, {0, 0},
        {0, 0}, {98, 9},
        {-9, -12}, {0, 0} });
    ASSERT_EQ(AB, A * B);
}

// Test for performance measure
// TEST(MatrixCCSPerformance, Sequential) {
//     MatrixCCS A = MatrixCCS(1000, 1000, 50000);
//     MatrixCCS B = MatrixCCS(1000, 1000, 50000);
//     A.FillRandom();
//     B.FillRandom();
//     ASSERT_NO_THROW(A * B);
// }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
