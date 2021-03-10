// Copyright 2021 Kochankov Ilya
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "./shell_sort_simple.h"

TEST(getRandomVector, no_exceptions) {
    ASSERT_NO_THROW(getRandomVector(100));
}

TEST(getRandomVector, wrong_size) {
    ASSERT_ANY_THROW(getRandomVector(-100));
}

TEST(getRandomVector, works) {
    auto vect = getRandomVector(100);
    ASSERT_EQ(static_cast<int>(vect.size()), 100);
}

TEST(shell_sort, no_exceptions) {
    auto vect = getRandomVector(100);
    ASSERT_NO_THROW(shell_sort(vect));
}

TEST(shell_sort, size_one_no_exceptions) {
    auto vect = getRandomVector(1);
    ASSERT_NO_THROW(shell_sort(vect));
}

TEST(shell_sort, size_two_no_exceptions) {
    auto vect = getRandomVector(2);
    ASSERT_NO_THROW(shell_sort(vect));
}

TEST(shell_sort, works_size_two) {
    auto vect = std::vector<double>({2, 1});
    auto sorted = shell_sort(vect);
    ASSERT_EQ(sorted, std::vector<double>({1, 2}));
}

TEST(shell_sort, works_size_three) {
    auto vect = std::vector<double>({3, 2, 1});
    auto sorted = shell_sort(vect);
    ASSERT_EQ(sorted, std::vector<double>({1, 2, 3}));
}

TEST(shell_sort, works_size_five) {
    auto vect = std::vector<double>({3, 2, 1, 6, 7});
    auto sorted = shell_sort(vect);
    ASSERT_EQ(sorted, std::vector<double>({1, 2, 3, 6, 7}));
}

TEST(shell_sort, works_size_zero) {
    auto vect = std::vector<double>();
    auto sorted = shell_sort(vect);
    ASSERT_EQ(sorted, std::vector<double>());
}

TEST(shell_sort, works_random_size_100) {
    auto vect = getRandomVector(100);
    auto sorted = shell_sort(vect);
    std::sort(vect.begin(), vect.end());
    ASSERT_EQ(vect, sorted);
}

TEST(shell_sort, works_random_size_1000) {
    auto vect = getRandomVector(1000);
    auto sorted = shell_sort(vect);
    std::sort(vect.begin(), vect.end());
    ASSERT_EQ(vect, sorted);
}

TEST(shell_sort, works_random_size_10000) {
    auto vect = getRandomVector(10000);
    auto sorted = shell_sort(vect);
    std::sort(vect.begin(), vect.end());
    ASSERT_EQ(vect, sorted);
}

TEST(merge, no_exceptions) {
    auto vect_a = getRandomVector(100);
    auto vect_b = getRandomVector(100);
    ASSERT_NO_THROW(merge(vect_a, vect_b));
}

TEST(merge, no_exceptions_different_size) {
    auto vect_a = getRandomVector(10);
    auto vect_b = getRandomVector(100);
    ASSERT_NO_THROW(merge(vect_a, vect_b));
}

TEST(merge, no_exceptions_null_size) {
    auto vect_a = getRandomVector(0);
    auto vect_b = getRandomVector(0);
    ASSERT_NO_THROW(merge(vect_a, vect_b));
}

TEST(merge, works_size_2) {
    auto vect_a = std::vector<double>({6, 7});
    auto vect_b = std::vector<double>({1, 2});
    auto merged = merge(vect_a, vect_b);
    ASSERT_EQ(merged, std::vector<double>({1, 2, 6, 7}));
}

TEST(merge, works_size_5) {
    auto vect_a = std::vector<double>({6, 7, 8, 9, 10});
    auto vect_b = std::vector<double>({1, 2, 3, 4, 5});
    auto merged = merge(vect_a, vect_b);
    ASSERT_EQ(merged, std::vector<double>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}));
}

TEST(merge, works_random_size_1) {
    auto vect_a = getRandomVector(1);
    auto vect_b = getRandomVector(1);
    auto merged = merge(vect_a, vect_b);
    for (int i = 0; i < static_cast<int>(vect_a.size()) - 1; ++i) {
        ASSERT_TRUE(merged[i] <= merged[i+1]);
    }
}

TEST(merge, works_random_size_5) {
    auto vect_a = getRandomVector(5);
    auto vect_b = getRandomVector(5);
    vect_a = shell_sort(vect_a);
    vect_b = shell_sort(vect_b);
    auto merged = merge(vect_a, vect_b);
    for (int i = 0; i < static_cast<int>(vect_a.size()) - 1; ++i) {
        ASSERT_TRUE(merged[i] <= merged[i+1]);
    }
}

TEST(merge, works_random_size_100) {
    auto vect_a = getRandomVector(100);
    auto vect_b = getRandomVector(100);
    vect_a = shell_sort(vect_a);
    vect_b = shell_sort(vect_b);
    auto merged = merge(vect_a, vect_b);
    for (int i = 0; i < static_cast<int>(vect_a.size()) - 1; ++i) {
        ASSERT_TRUE(merged[i] <= merged[i+1]);
    }
}

TEST(merge, works_random_size_1000) {
    auto vect_a = getRandomVector(1000);
    auto vect_b = getRandomVector(1000);
    vect_a = shell_sort(vect_a);
    vect_b = shell_sort(vect_b);
    auto merged = merge(vect_a, vect_b);
    for (int i = 0; i < static_cast<int>(vect_a.size()) - 1; ++i) {
        ASSERT_TRUE(merged[i] <= merged[i+1]);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
