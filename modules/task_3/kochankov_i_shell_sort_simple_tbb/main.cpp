// Copyright 2021 Kochankov Ilya
#include <tbb/tbb.h>
#include <omp.h>
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "./shell_sort_simple_tbb.h"


TEST(shell_sort_tbb, no_exceptions) {
    auto vect = getRandomVector(100);
    ASSERT_NO_THROW(shell_sort_tbb(vect));
}

TEST(shell_sort_tbb, size_one_no_exceptions) {
    auto vect = getRandomVector(1);
    ASSERT_NO_THROW(shell_sort_tbb(vect));
}

TEST(shell_sort_tbb, size_two_no_exceptions) {
    auto vect = getRandomVector(2);
    ASSERT_NO_THROW(shell_sort_tbb(vect));
}

TEST(shell_sort_tbb, works_size_two) {
    auto vect = std::vector<double>({2, 1});
    auto sorted = shell_sort_tbb(vect);
    ASSERT_EQ(sorted, std::vector<double>({1, 2}));
}

TEST(shell_sort_tbb, works_size_three) {
    auto vect = std::vector<double>({3, 2, 1});
    auto sorted = shell_sort_tbb(vect);
    ASSERT_EQ(sorted, std::vector<double>({1, 2, 3}));
}

TEST(shell_sort_tbb, works_size_five) {
    auto vect = std::vector<double>({3, 2, 1, 6, 7});
    auto sorted = shell_sort_tbb(vect);
    ASSERT_EQ(sorted, std::vector<double>({1, 2, 3, 6, 7}));
}

TEST(shell_sort_tbb, works_size_zero) {
    auto vect = std::vector<double>();
    auto sorted = shell_sort_tbb(vect);
    ASSERT_EQ(sorted, std::vector<double>());
}

TEST(shell_sort_tbb, works_random_size_100) {
    auto vect = getRandomVector(100);
    auto sorted = shell_sort_tbb(vect);
    std::sort(vect.begin(), vect.end());
    ASSERT_EQ(vect, sorted);
}

TEST(shell_sort_tbb, works_random_size_1000) {
    auto vect = getRandomVector(1000);
    auto sorted = shell_sort_tbb(vect);
    std::sort(vect.begin(), vect.end());
    ASSERT_EQ(vect, sorted);
}

TEST(shell_sort_tbb, works_random_size_10000) {
    auto vect = getRandomVector(10000);
    auto sorted = shell_sort_tbb(vect);
    std::sort(vect.begin(), vect.end());
    ASSERT_EQ(vect, sorted);
}

TEST(shell_sort_tbb, get_time) {
    auto vect = getRandomVector(1000000);

    tbb::tick_count t0 = tbb::tick_count::now();
    auto p_sorted = shell_sort_tbb(vect);
    tbb::tick_count t1 = tbb::tick_count::now();
    std::cout << "Parallel sort time: " << (t1 - t0).seconds() << std::endl;

    tbb::tick_count t2 = tbb::tick_count::now();
    auto l_sorted = shell_sort(vect);
    tbb::tick_count t3 = tbb::tick_count::now();
    std::cout << "Linear sort time: " << (t3 - t2).seconds() << std::endl;

    ASSERT_EQ(p_sorted, l_sorted);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
