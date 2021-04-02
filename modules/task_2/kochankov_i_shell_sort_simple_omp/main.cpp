// Copyright 2021 Kochankov Ilya
#include <omp.h>
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "./shell_sort_simple_omp.h"


TEST(shell_sort_omp, no_exceptions) {
    auto vect = getRandomVector(100);
    ASSERT_NO_THROW(shell_sort_omp(vect));
}

TEST(shell_sort_omp, size_one_no_exceptions) {
    auto vect = getRandomVector(1);
    ASSERT_NO_THROW(shell_sort_omp(vect));
}

TEST(shell_sort_omp, size_two_no_exceptions) {
    auto vect = getRandomVector(2);
    ASSERT_NO_THROW(shell_sort_omp(vect));
}

TEST(shell_sort_omp, works_size_two) {
    auto vect = std::vector<double>({2, 1});
    auto sorted = shell_sort_omp(vect);
    ASSERT_EQ(sorted, std::vector<double>({1, 2}));
}

TEST(shell_sort_omp, works_size_three) {
    auto vect = std::vector<double>({3, 2, 1});
    auto sorted = shell_sort_omp(vect);
    ASSERT_EQ(sorted, std::vector<double>({1, 2, 3}));
}

TEST(shell_sort_omp, works_size_five) {
    auto vect = std::vector<double>({3, 2, 1, 6, 7});
    auto sorted = shell_sort_omp(vect);
    ASSERT_EQ(sorted, std::vector<double>({1, 2, 3, 6, 7}));
}

TEST(shell_sort_omp, works_size_zero) {
    auto vect = std::vector<double>();
    auto sorted = shell_sort_omp(vect);
    ASSERT_EQ(sorted, std::vector<double>());
}

TEST(shell_sort_omp, works_random_size_100) {
    auto vect = getRandomVector(100);
    auto sorted = shell_sort_omp(vect);
    std::sort(vect.begin(), vect.end());
    ASSERT_EQ(vect, sorted);
}

TEST(shell_sort_omp, works_random_size_1000) {
    auto vect = getRandomVector(1000);
    auto sorted = shell_sort_omp(vect);
    std::sort(vect.begin(), vect.end());
    ASSERT_EQ(vect, sorted);
}

TEST(shell_sort_omp, works_random_size_10000) {
    auto vect = getRandomVector(10000);
    auto sorted = shell_sort_omp(vect);
    std::sort(vect.begin(), vect.end());
    ASSERT_EQ(vect, sorted);
}

TEST(shell_sort_omp, get_time) {
    auto vect = getRandomVector(1000000);

    double start = omp_get_wtime();
    auto p_sorted = shell_sort_omp(vect);
    double end = omp_get_wtime();
    std::cout << "Parallel sort time: " << end - start << std::endl;

    start = omp_get_wtime();
    auto l_sorted = shell_sort(vect);
    end = omp_get_wtime();
    std::cout << "Linear sort time: " << end - start << std::endl;

    ASSERT_EQ(p_sorted, l_sorted);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
