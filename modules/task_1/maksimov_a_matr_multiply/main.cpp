// Copyright 2021 Maksimov Andrey
#include <gtest/gtest.h>
#include <vector>
#include "./matrix_multiply.h"

TEST(Matr_mupltiply, Can_generate_matrix) {
    const int matrRows = 20;
    std::vector<double> matr = generateMatrix(matrRows);
    for (int i = 0; i < matrRows * matrRows; i++) {
        ASSERT_GT(matr[i], 0.0);
    }
}

TEST(Matr_mupltiply, Rows_not_equal) {
    std::vector<double> matr1 = { 2.0 };
    std::vector<double> matr2
        = { 4.0, 1.0,
            1.0, 1.0 };
    std::vector<double> expectedMatr = { 8.0 };

    ASSERT_ANY_THROW(mupltiplyMatrixByMatrix(matr1, matr2, 1, 2));
}

TEST(Matr_mupltiply, Correct_mupltiply_1x1) {
    std::vector<double> matr1 = { 2.0 };
    std::vector<double> matr2 = { 4.0 };
    std::vector<double> expectedMatr = { 8.0 };

    std::vector<double> resultMatr
        = mupltiplyMatrixByMatrix(matr1, matr2, 1, 1);
    ASSERT_EQ(expectedMatr[0], resultMatr[0]);
}

TEST(Matr_mupltiply, Correct_mupltiply_2x2) {
    std::vector<double> matr1
        = { 1.0, 2.0,
            3.0, 4.0 };
    std::vector<double> matr2
        = { 4.0, 2.0,
            6.0, 7.0 };
    std::vector<double> expectedMatr
        = { 16.0, 16.0,
            36.0, 34.0 };

    std::vector<double> resultMatr
        = mupltiplyMatrixByMatrix(matr1, matr2, 2, 2);
    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(expectedMatr[i], resultMatr[i]);
    }
}

TEST(Matr_mupltiply, Correct_mupltiply_3x3) {
    std::vector<double> matr1
        = { 1.0, 2.0, 3.0,
            4.0, 5.0, 6.0,
            7.0, 7.0, 8.0 };
    std::vector<double> matr2
        = { 4.0, 2.0, 3.0,
            6.0, 7.0, 8.0,
            2.0, 1.0, 9.0 };
    std::vector<double> expectedMatr
        = { 22.0, 19.0, 46.0,
            58.0, 49.0, 106.0,
            86.0, 71.0, 149.0 };

    std::vector<double> resultMatr
        = mupltiplyMatrixByMatrix(matr1, matr2, 3, 3);
    for (int i = 0; i < 9; i++) {
        ASSERT_EQ(expectedMatr[i], resultMatr[i]);
    }
}

TEST(Matr_mupltiply, Correct_mupltiply_4x4) {
    std::vector<double> matr1
        = { 1.0, 2.0, 3.0, 4.0,
            4.0, 5.0, 6.0, 7.0,
            7.0, 7.0, 8.0, 9.0,
            2.0, 1.0, 2.0, 1.0 };
    std::vector<double> matr2
        = { 4.0, 2.0, 3.0, 3.0,
            6.0, 7.0, 8.0, 8.0,
            2.0, 1.0, 9.0, 1.0,
            6.0, 7.0, 8.0, 8.0, };
    std::vector<double> expectedMatr
        = { 46.0, 47.0, 78.0, 54.0,
            100.0, 98.0, 162.0, 114.0,
            140.0, 134.0, 221.0, 157.0,
            24.0, 20.0, 40.0, 24.0 };

    std::vector<double> resultMatr
        = mupltiplyMatrixByMatrix(matr1, matr2, 4, 4);
    for (int i = 0; i < 16; i++) {
        ASSERT_EQ(expectedMatr[i], resultMatr[i]);
    }
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
