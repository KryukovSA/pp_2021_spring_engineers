// Copyright 2021 Khismatulina Karina
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "../../../modules/task_1/khismatulina_k_gradient/seq.h"

TEST(gradient, create_vec_with_negative_size) {
    ASSERT_ANY_THROW(getRandomVector(-2));
}

TEST(gradient, check_multVV) {
    int size = 2;
    std::vector<double> v1(size);
    std::vector<double> v2(size);
    v1[0] = 2;
    v1[1] = 3;
    v2[0] = 1;
    v2[1] = 4;
    double rightRes = 14;
    ASSERT_EQ(rightRes, multVV(v1, v2));
}

TEST(gradient, check_multMV_1) {
    int size = 4;
    std::vector<double> matrix(size);
    std::vector<double> vec(size);
    vec[0] = 2;
    vec[1] = 1;
    vec[2] = 2;
    vec[3] = 4;
    matrix[0] = 3;
    matrix[1] = 2;
    matrix[2] = 3;
    matrix[3] = 2;

    std::vector<double> rightRes(matrix.size(), 1);
    rightRes[0] = 22;
    std::vector<double> myRes = multMV(matrix, vec);
    int check = 1;
    for (size_t i = 0; i < myRes.size(); ++i) {
        if (myRes[i] != rightRes[i]) check = 0;
    }
    ASSERT_EQ(check, 1);
}

TEST(gradient, check_multMV_2) {
    std::vector<double> matrix(4);
    std::vector<double> vec(2);
    vec[0] = 2;
    vec[1] = 1;

    matrix[0] = 3;
    matrix[1] = 2;
    matrix[2] = 3;
    matrix[3] = 2;

    std::vector<double> rightRes(matrix.size(), 1);
    rightRes[0] = 8;
    rightRes[1] = 8;

    std::vector<double> myRes = multMV(matrix, vec);
    int check = 1;
    for (size_t i = 0; i < myRes.size(); ++i) {
        if (myRes[i] != rightRes[i]) check = 0;
    }
    ASSERT_EQ(check, 1);
}

TEST(gradient, gradient_test) {
    int size = 3;
    std::vector<double> vec(size);
    std::vector<double> matrix(size * size);
    vec[0] = 2;
    vec[1] = 1;
    vec[2] = 3;

    matrix[0] = 2;
    matrix[1] = 1;
    matrix[2] = 2;
    matrix[3] = 1;
    matrix[4] = 3;
    matrix[5] = 0;
    matrix[6] = 2;
    matrix[7] = 0;
    matrix[8] = 3;
    std::vector<double> rightRes(size);
    rightRes[0] = 0.25;
    rightRes[1] = 0.21;
    rightRes[2] = 0.68;
    std::vector<double> myRes = gradientSeq(matrix, vec, size);
    for (size_t i = 0; i < myRes.size(); ++i) {
        ASSERT_NEAR(myRes[i], rightRes[i], 0.5);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
