// Copyright 2020 Egorov Kirill
#include <gtest/gtest.h>
#include <vector>
#include "../../../modules/task_1/egorov_k_gauss_filter_seq/egorov_k_gauss_filter_seq.h"

TEST(basic_functions_tests, clamp_test) {
    int num = 0;

    ASSERT_EQ(clamp(num, -5, 5), 0);
}

TEST(basic_functions_tests, clamp_test_2) {
    int num = -6;

    ASSERT_EQ(clamp(num, -5, 5), -5);
}

TEST(basic_functions_tests, clamp_test_3) {
    int num = 6;

    ASSERT_EQ(clamp(num, -5, 5), 5);
}

TEST(exceptions_tests, kernel_calculation) {
    std::vector<float> test;

    ASSERT_NO_THROW(test = calculateKernel3x3(3));
}

TEST(exceptions_tests, filter_apply) {
    std::vector<int> test = getRandomVector(64);
    std::vector<int> res(test.size());

    ASSERT_NO_THROW(res = filterApply(test, 8, 8, 3));
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
