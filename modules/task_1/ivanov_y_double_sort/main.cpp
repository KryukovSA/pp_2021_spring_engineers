// Copyright 2021 Ivanov Yaroslav
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "./sort_double.h"

using std::vector;

TEST(Local_compare, Test_works_byte_sort) {
    const int size = 100;
    std::vector<double> vec(size);
    vec = generateDouble(size);
    ASSERT_NO_THROW(loc_sort(vec, size));
}

TEST(Local_compare, Test_works_bubble_sort) {
    const int size = 100;
    std::vector<double> vec(size);
    vec = generateDouble(size);
    ASSERT_NO_THROW(BubbleForCompare(vec, size));
}

TEST(Local_compare, Test_size_one_no_exceptions) {
    const int size = 1;
    std::vector<double> vec(size);
    vec = generateDouble(size);
    ASSERT_NO_THROW(loc_sort(vec, size));
}

TEST(Local_compare, Test_size_four_eq_real_sort_mas) {
    const int size = 4;
    std::vector<double> vec(size);
    vec = generateDouble(size);
    std::vector<double> loc{ 10.0, 11.0, 14.0, 16.0 };
    std::vector<double> loc1{ 14.0, 16.0, 11.0, 10.0 };
    for (int i = 0; i < 4; i++) {
        vec[i] = loc1[i];
    }
    vec = loc_sort(vec, size);
    for (int i = 0; i < 4; i++) {
        loc1[i] = vec[i];
    }
    ASSERT_EQ(loc1, loc);
}

TEST(Local_compare, Test_seq_compare_100) {
    const int size = 100;
    std::vector<double> vec(size);
    vec = generateDouble(size);
    vec = loc_sort(vec, size);
    ASSERT_EQ(vec, BubbleForCompare(vec, size));
}

TEST(Local_compare, Test_seq_compare_1000) {
    const int size = 1000;
    std::vector<double> vec(size);
    vec = generateDouble(size);
    vec = loc_sort(vec, size);
    ASSERT_EQ(vec, BubbleForCompare(vec, size));
}

TEST(Local_compare, Test_negativ_size) {
    const int size = -10;
    ASSERT_ANY_THROW(generateDouble(size));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
