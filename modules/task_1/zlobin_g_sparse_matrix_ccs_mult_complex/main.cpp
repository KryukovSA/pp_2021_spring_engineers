// Copyright 2021 Zlobin George
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "./matrix_ccs_mult.h"

// Tests for Constructor MatrixCCS(int nCollumns, int nRows, int nNotZero);
TEST(Matrix_CCS_Constructor_From_NCollumns_NRows_NNotZero,
        Throw_If_Incorrect_NCollumns) {
    ASSERT_ANY_THROW(MatrixCCS(-10, 10, 3));
}
TEST(Matrix_CCS_Constructor_From_NCollumns_NRows_NNotZero,
        Throw_If_Incorrect_NRows) {
    ASSERT_ANY_THROW(MatrixCCS(10, 0, 3));
}
TEST(Matrix_CCS_Constructor_From_NCollumns_NRows_NNotZero,
        Throw_If_Incorrect_NNotZero) {
    ASSERT_ANY_THROW(MatrixCCS(10, 10, -3));
}
TEST(Matrix_CCS_Constructor_From_NCollumns_NRows_NNotZero,
        Throw_If_NNotZero_More_Than_Available) {
    ASSERT_ANY_THROW(MatrixCCS(10, 10, 101));
}
TEST(Matrix_CCS_Constructor_From_NCollumns_NRows_NNotZero,
        No_Throw_With_Correct_Parameters) {
    ASSERT_NO_THROW(MatrixCCS(10, 10, 3));
}
TEST(Matrix_CCS_Constructor_From_NCollumns_NRows_NNotZero,
        Can_Create_Matrix_With_Zero_Elements) {
    ASSERT_NO_THROW(MatrixCCS(10, 10, 0));
}

// Tests for Constructor MatrixCCS(nCollumns, nRows, matrix);
TEST(Matrix_CCS_Constructor_From_NCollumns_NRows_Matrix,
        Throw_If_Incorrect_NCollumns) {
    ASSERT_ANY_THROW(MatrixCCS(0, 2,
        { complex_int(2, 3),     complex_int(0, 0),
        complex_int(0, -1),    complex_int(-7, 0) }));
}
TEST(Matrix_CCS_Constructor_From_NCollumns_NRows_Matrix,
        Throw_If_Incorrect_NRows) {
    ASSERT_ANY_THROW(MatrixCCS(2, -3,
        { complex_int(0, 0),     complex_int(2, 3),
        complex_int(0, -1),    complex_int(-7, 0) }));
}
TEST(Matrix_CCS_Constructor_From_NCollumns_NRows_Matrix,
        Throw_If_Matrix_Has_Incorrect_Size) {
    ASSERT_ANY_THROW(MatrixCCS(2, 2,
        { complex_int(0, 0),     complex_int(2, 3),      complex_int(7, 0),
        complex_int(0, -1),    complex_int(-7, 0),     complex_int(0, 0),
        complex_int(0, 0),     complex_int(0, 0),      complex_int(-3, 10) }));
}
TEST(Matrix_CCS_Constructor_From_NCollumns_NRows_Matrix,
        No_Throw_With_Correct_Parameters) {
    ASSERT_NO_THROW(MatrixCCS(3, 3,
        { complex_int(0, 0),     complex_int(2, 3),      complex_int(7, 0),
        complex_int(0, -1),    complex_int(-7, 0),     complex_int(0, 0),
        complex_int(0, 0),     complex_int(0, 0),      complex_int(-3, 10) }));
}
TEST(Matrix_CCS_Constructor_From_NCollumns_NRows_Matrix,
        Can_Create_Matrix_With_Zero_Elements) {
    ASSERT_NO_THROW(MatrixCCS(3, 3,
        { complex_int(0, 0),     complex_int(0, 0),      complex_int(0, 0),
        complex_int(0, 0),     complex_int(0, 0),      complex_int(0, 0),
        complex_int(0, 0),     complex_int(0, 0),      complex_int(0, 0) }));
}

// Tests for Constructor MatrixCCS(int nCollumns, int nRows,
//                                 std::vector<int> collumnsIndexes,
//                                 std::vector<int> rows,
//                                 std::vector<complex_int> values);
TEST(Matrix_CCS_Constructor_From_Direct_Given_Fields,
        Throw_If_Incorrect_NCollumns) {
    ASSERT_ANY_THROW(MatrixCCS(-2, 2,
        { 0, 0, 2 },
        { 0, 1 },
        { complex_int(-7, 0), complex_int(0, -10) }));
}
TEST(Matrix_CCS_Constructor_From_Direct_Given_Fields,
        Throw_If_Incorrect_NRows) {
    ASSERT_ANY_THROW(MatrixCCS(2, 0,
        { 0, 0, 2 },
        { 0, 1 },
        { complex_int(-7, 0), complex_int(0, -10) }));
}
TEST(Matrix_CCS_Constructor_From_Direct_Given_Fields,
        Throw_If_Given_More_Values_Than_Matrix_Size) {
    ASSERT_ANY_THROW(MatrixCCS(2, 0,
        { 0, 0, 2 },
        { 0, 1 },
        { complex_int(-7, 0), complex_int(0, -10) }));
}
TEST(Matrix_CCS_Constructor_From_Direct_Given_Fields,
        Throw_If_Incorrect_Collumns_Indexes) {
    ASSERT_ANY_THROW(MatrixCCS(2, 2,
        { 0, 0, 2, 2 },
        { 0, 1 },
        { complex_int(-7, 0), complex_int(0, -10) }));
}
TEST(Matrix_CCS_Constructor_From_Direct_Given_Fields,
        Throw_If_Rows_Has_Incorrect_Value) {
    ASSERT_ANY_THROW(MatrixCCS(2, 2,
        { 0, 0, 2 },
        { 0, 2 },
        { complex_int(-7, 0), complex_int(0, -10) }));
}
TEST(Matrix_CCS_Constructor_From_Direct_Given_Fields,
        No_Throw_With_Correct_Parameters) {
    ASSERT_NO_THROW(MatrixCCS(2, 2,
        { 0, 0, 2 },
        { 0, 1 },
        { complex_int(-7, 0), complex_int(0, -10) }));
}
TEST(Matrix_CCS_Constructor_From_Direct_Given_Fields,
        Can_Create_Matrix_With_Zero_Elements) {
    ASSERT_NO_THROW(MatrixCCS(2, 2,
        { 0, 0, 0},
        {},
        {}));
}

// Tests for constructors MatrixCCS are equivalent
TEST(Matrix_CCS_Constructor_Are_Equivalent, Matrix_With_Zero_Elements) {
    EXPECT_EQ(MatrixCCS(3, 3,
        { complex_int(0, 0),     complex_int(0, 0),      complex_int(0, 0),
        complex_int(0, 0),     complex_int(0, 0),      complex_int(0, 0),
        complex_int(0, 0),     complex_int(0, 0),      complex_int(0, 0) }),
              MatrixCCS(3, 3,
        { 0, 0, 0, 0},
        {},
        {}));
}
TEST(Matrix_CCS_Constructor_Are_Equivalent, Square_Matrix) {
    EXPECT_EQ(MatrixCCS(3, 3,
        { complex_int(0, 0),     complex_int(2, 3),      complex_int(7, 0),
        complex_int(0, -1),    complex_int(-7, 0),     complex_int(0, 0),
        complex_int(0, 0),     complex_int(0, 0),      complex_int(-3, 10) }),
              MatrixCCS(3, 3,
        { 0, 1, 3, 5 },
        { 1, 0, 1, 0, 2 },
        { complex_int(0, -1),    complex_int(2, 3),      complex_int(-7, 0),
        complex_int(7, 0),     complex_int(-3, 10) }));
}
TEST(Matrix_CCS_Constructor_Are_Equivalent, Row) {
    EXPECT_EQ(MatrixCCS(3, 1,
        { complex_int(0, 0),     complex_int(2, 3),      complex_int(7, 0) }),
              MatrixCCS(3, 1,
        { 0, 0, 1, 2 },
        { 0, 0 },
        { complex_int(2, 3),     complex_int(7, 0) }));
}
TEST(Matrix_CCS_Constructor_Are_Equivalent, Collumn) {
    EXPECT_EQ(MatrixCCS(1, 3,
        { complex_int(0, 0),
        complex_int(0, -1),
        complex_int(0, 0) }),
              MatrixCCS(1, 3,
        { 0, 1 },
        { 1 },
        { complex_int(0, -1) }));
}
TEST(Matrix_CCS_Constructor_Are_Equivalent, Not_Square_Matrix) {
    EXPECT_EQ(MatrixCCS(3, 2,
        { complex_int(0, 0),     complex_int(2, 3),      complex_int(7, 0),
        complex_int(0, -1),    complex_int(-7, 0),     complex_int(0, 0) }),
              MatrixCCS(3, 2,
        { 0, 1, 3, 4 },
        { 1, 0, 1, 0 },
        { complex_int(0, -1),    complex_int(2, 3),      complex_int(-7, 0),
        complex_int(7, 0) }));
}
TEST(Matrix_CCS_Constructor_Are_Equivalent, Different_Sizes_Not_Same) {
    EXPECT_FALSE(MatrixCCS(3, 3,
        { complex_int(0, 0),     complex_int(2, 3),      complex_int(7, 0),
        complex_int(0, -1),    complex_int(-7, 0),     complex_int(0, 0),
        complex_int(0, 0),     complex_int(0, 0),      complex_int(-3, 10) }) ==
              MatrixCCS(3, 2,
        { 0, 1, 3, 4 },
        { 1, 0, 1, 0 },
        { complex_int(0, -1),    complex_int(2, 3),      complex_int(-7, 0),
        complex_int(7, 0) }));
}
TEST(Matrix_CCS_Constructor_Are_Equivalent, Different_Values_Not_Same) {
    EXPECT_FALSE(MatrixCCS(3, 3,
        { complex_int(0, 0),     complex_int(2, 3),      complex_int(7, 0),
        complex_int(0, -1),    complex_int(7, 0),     complex_int(0, 0),
        complex_int(0, 0),     complex_int(0, 0),      complex_int(-3, 10) }) ==
              MatrixCCS(3, 3,
        { 0, 1, 3, 5 },
        { 1, 0, 1, 0, 2 },
        { complex_int(0, -1),    complex_int(2, 3),      complex_int(-7, 0),
        complex_int(7, 0),     complex_int(-3, 10) }));
}

// Tests for FillRandom(unsigned seed = 132, int min = -1000, int max = 1000);
TEST(Matrix_CCS_Fill_With_Random_Values, Can_Fill_Matrix) {
    MatrixCCS A = MatrixCCS(3, 3, 0);
    ASSERT_NO_THROW(A.FillRandom());
}
TEST(Matrix_CCS_Fill_With_Random_Values, Same_Seed_Same_Matrix) {
    MatrixCCS A = MatrixCCS(3, 3, 0);
    MatrixCCS B = A;
    A.FillRandom();
    B.FillRandom();
    EXPECT_EQ(A, B);
}

// Tests for Transpose()
TEST(Matrix_CCS_Transpose, Can_Transpose) {
    MatrixCCS A = MatrixCCS(3, 3,
        { complex_int(0, 0),     complex_int(2, 3),      complex_int(7, 0),
        complex_int(0, -1),    complex_int(-7, 0),     complex_int(0, 0),
        complex_int(0, 0),     complex_int(0, 0),      complex_int(-3, 10) });
    ASSERT_NO_THROW(A.Transpose());
}
TEST(Matrix_CCS_Transpose, Square_Matrix) {
    MatrixCCS A = MatrixCCS(3, 3,
        { complex_int(0, 0),     complex_int(2, 3),      complex_int(7, 0),
        complex_int(0, -1),    complex_int(-7, 0),     complex_int(0, 0),
        complex_int(0, 0),     complex_int(0, 0),      complex_int(-3, 10) });
    MatrixCCS AT = A.Transpose();
    MatrixCCS ATref = MatrixCCS(3, 3,
        { complex_int(0, 0),     complex_int(0, -1),      complex_int(0, 0),
        complex_int(2, 3),     complex_int(-7, 0),      complex_int(0, 0),
        complex_int(7, 0),     complex_int(0, 0),       complex_int(-3, 10) });
    EXPECT_EQ(ATref, AT);
    EXPECT_EQ(A, AT.Transpose());
}
TEST(Matrix_CCS_Transpose, Row) {
    MatrixCCS A = MatrixCCS(3, 1,
        { complex_int(0, 0),     complex_int(2, 3),      complex_int(7, 0) });
    MatrixCCS AT = A.Transpose();
    MatrixCCS ATref = MatrixCCS(1, 3,
        { complex_int(0, 0),
        complex_int(2, 3),
        complex_int(7, 0) });
    EXPECT_EQ(ATref, AT);
    EXPECT_EQ(A, AT.Transpose());
}
TEST(Matrix_CCS_Transpose, Not_Square_Matrix) {
    MatrixCCS A = MatrixCCS(3, 2,
        { complex_int(0, 0),     complex_int(2, 3),      complex_int(7, 0),
        complex_int(0, -1),    complex_int(-7, 0),     complex_int(0, 0) });
    MatrixCCS AT = A.Transpose();
    MatrixCCS ATref = MatrixCCS(2, 3,
        { complex_int(0, 0),     complex_int(0, -1),
        complex_int(2, 3),     complex_int(-7, 0),
        complex_int(7, 0),     complex_int(0, 0) });
    EXPECT_EQ(ATref, AT);
    EXPECT_EQ(A, AT.Transpose());
}

// Tests for Multiplication
TEST(Matrix_CCS_Multiplication, Throw_If_Not_Corresponding_Matrices) {
    MatrixCCS A = MatrixCCS(3, 2,
        { complex_int(0, 0),     complex_int(2, 3),      complex_int(7, 0),
        complex_int(0, -1),    complex_int(-7, 0),     complex_int(0, 0) });
    MatrixCCS B = MatrixCCS(2, 4,
        { complex_int(0, 0),     complex_int(0, -1),
        complex_int(2, 3),     complex_int(-7, 0),
        complex_int(7, 0),     complex_int(0, 0),
        complex_int(0, -10),   complex_int(20, 0) });
    ASSERT_ANY_THROW(A * B);
}
TEST(Matrix_CCS_Multiplication, Can_Multiply_Corresponding_Matrices) {
    MatrixCCS A = MatrixCCS(3, 2,
        { complex_int(0, 0),     complex_int(2, 3),      complex_int(7, 0),
        complex_int(0, -1),    complex_int(-7, 0),     complex_int(0, 0) });
    MatrixCCS B = MatrixCCS(2, 3,
        { complex_int(0, 0),     complex_int(0, -1),
        complex_int(2, 3),     complex_int(-7, 0),
        complex_int(7, 0),     complex_int(0, 0) });
    ASSERT_NO_THROW(A * B);
}
TEST(Matrix_CCS_Multiplication, Myltiply_Numbers) {
    MatrixCCS A = MatrixCCS(1, 1,
        { complex_int(20, -30) });
    MatrixCCS B = MatrixCCS(1, 1,
        { complex_int(86, 360) });
    MatrixCCS AB = MatrixCCS(1, 1,
        { complex_int(12520, 4620) });
    ASSERT_EQ(AB, A * B);
}
TEST(Matrix_CCS_Multiplication, Myltiply_On_Zero_Matrix) {
    MatrixCCS A = MatrixCCS(3, 2,
        { complex_int(0, 0),    complex_int(20, 0),     complex_int(7, 0),
        complex_int(8, 0),    complex_int(-7, 0),     complex_int(0, 0) });
    MatrixCCS B = MatrixCCS(2, 3,
        { complex_int(0, 0),     complex_int(0, 0),
        complex_int(0, 0),     complex_int(0, 0),
        complex_int(0, 0),     complex_int(0, 0) });
    MatrixCCS AB = MatrixCCS(2, 2,
        { complex_int(0, 0),     complex_int(0, 0),
        complex_int(0, 0),    complex_int(0, 0) });
    ASSERT_EQ(AB, A * B);
}
TEST(Matrix_CCS_Multiplication, Myltiply_On_Singular_Matrix) {
    MatrixCCS A = MatrixCCS(2, 2,
        { complex_int(1, 0),    complex_int(0, 0),
        complex_int(0, 0),    complex_int(1, 0) });
    MatrixCCS B = MatrixCCS(2, 2,
        { complex_int(3, 20),     complex_int(4, 0),
        complex_int(0, -3),     complex_int(0, 0) });
    ASSERT_EQ(B, A * B);
}
TEST(Matrix_CCS_Multiplication, Matrix_Multiplication_Example_1) {
    MatrixCCS A = MatrixCCS(3, 2,
        { complex_int(0, 0),    complex_int(20, 0),     complex_int(7, 0),
        complex_int(8, 0),    complex_int(-7, 0),     complex_int(0, 0) });
    MatrixCCS B = MatrixCCS(2, 3,
        { complex_int(0, 0),     complex_int(0, 0),
        complex_int(4, 0),     complex_int(-7, 0),
        complex_int(0, 0),     complex_int(0, 0) });
    MatrixCCS AB = MatrixCCS(2, 2,
        { complex_int(80, 0),     complex_int(-140, 0),
        complex_int(-28, 0),    complex_int(49, 0) });
    ASSERT_EQ(AB, A * B);
}
TEST(Matrix_CCS_Multiplication, Matrix_Multiplication_Example_2) {
    MatrixCCS A = MatrixCCS(3, 4,
        { complex_int(0, 0),     complex_int(0, 0),     complex_int(0, 0),
        complex_int(0, 0),     complex_int(-7, 0),    complex_int(0, 0),
        complex_int(0, 0),     complex_int(0, 0),     complex_int(4, 7),
        complex_int(4, -3),    complex_int(0, 0),     complex_int(0, 0)});
    MatrixCCS B = MatrixCCS(2, 3,
        { complex_int(0, -3),    complex_int(0, 0),
        complex_int(0, 0),     complex_int(0, 0),
        complex_int(0, 0),     complex_int(7, -10) });
    MatrixCCS AB = MatrixCCS(2, 4,
        { complex_int(0, 0),    complex_int(0, 0),
        complex_int(0, 0),    complex_int(0, 0),
        complex_int(0, 0),    complex_int(4, 7) * complex_int(7, -10),
        complex_int(4, -3) * complex_int(0, -3),    complex_int(0, 0) });
    ASSERT_EQ(AB, A * B);
}

// Test for performance measure
// TEST(Matrix_CCS_Performance, Sequential) {
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
