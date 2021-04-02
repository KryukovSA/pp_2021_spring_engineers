// Copyright 2021 Bulychev Andrey
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "./shell_sort_simple.h"

TEST(Sequential, Get_random_vector_with_correct_size) {
    ASSERT_NO_THROW(getRandomVector(1000));
}

TEST(Sequential, Get_random_vector_with_wrong_size) {
    ASSERT_ANY_THROW(getRandomVector(-2));
}

TEST(Sequential, Work_of_sort) {
    std::vector<double> vec = std::vector<double>({112, 6, 0, 17.8, 96});
    std::vector<double> sort = Shell_sort(vec);
    ASSERT_EQ(sort, std::vector<double>({0, 6, 17.8, 96, 112}));
}

TEST(Sequential, Correct_work_sort_big_size) {
    std::vector<double> vec = getRandomVector(10000);
    ASSERT_NO_THROW(Shell_sort(vec));
}

TEST(Sequential, Test_work_of_merge) {
    std::vector<double> vec1 = std::vector<double>({ 0, 6, 17.9, 96, 112 });
    std::vector<double> vec2 = std::vector<double>({ 19, 95, 100, 127, 340 });
    std::vector<double> tmp = std::vector<double>({ 0, 6, 17.9, 19, 95, 96, 100, 112, 127, 340 });
    std::vector<double> sort = Merge(vec1, vec2);
    ASSERT_EQ(tmp, sort);
}

TEST(Sequential, Correct_work_merge_big_size) {
    std::vector<double> vec1 = getRandomVector(10000);
    std::vector<double> vec2 = getRandomVector(16397);
    ASSERT_NO_THROW(Merge(vec1, vec2));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
