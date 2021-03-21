// Copyright 2021 Frolova Olga
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "../../../modules/task_1/frolova_o_radix_sort_batcher_merge/radix_sort_batcher_merge.h"

TEST(getRandomVector, check_size) {
    std::vector<double> vect = getRandomVector(100);
    ASSERT_EQ((int)vect.size(), 100);
}

TEST(checkMinorFunction, maxVal1) {
    std::vector<double> vect = std::vector<double>({3.0, 6.2, 1.0, 6.1, 7.0});
    ASSERT_EQ(maxVal(vect), 7);
}

TEST(checkMinorFunction, maxVal2) {
    std::vector<double> vect = std::vector<double>({13, 168, 1, 1090, -5});
    ASSERT_EQ(maxVal(vect), 1090);
}

TEST(checkMinorFunction, countRadix) {
    ASSERT_EQ(countRadix(7.0), 1);
    ASSERT_EQ(countRadix(7.1), 1);
    ASSERT_EQ(countRadix(13), 2);
    ASSERT_EQ(countRadix(136), 3);
    ASSERT_EQ(countRadix(1909), 4);
}

TEST(checkMinorFunction, getRemander) {
    ASSERT_EQ(getRemainder(6.0), 0);
    ASSERT_EQ(getRemainder(6.2), 2);
    ASSERT_EQ(getRemainder(12.6), 6);
    ASSERT_EQ(getRemainder(12.123), 123);
    ASSERT_EQ(getRemainder(12.5912), 5912);
}

TEST(checkMinorFunction, negRadix) {
    ASSERT_EQ(countNegRadix(12.12), 2);
    ASSERT_EQ(countNegRadix(12.123), 3);
    ASSERT_EQ(countNegRadix(12.1), 1);
    ASSERT_EQ(countNegRadix(12), 0);
}

TEST(checkMinorFunction, checkVector) {
    std::vector<double> vect = std::vector<double>({3.0, 6.2, 1.0, 6.1, 7.0});
    std::vector<double> checked = checkVector(vect);
    ASSERT_EQ(checked, std::vector<double>({1.0, 3.0, 6.1, 6.2, 7.0}));
}

TEST(radix_sort, size_two) {
    std::vector<double> vect = std::vector<double>({2.0, 1.0});
    std::vector<double> sorted = radixSort(vect);
    ASSERT_EQ(sorted, std::vector<double>({1, 2}));
}

TEST(radix_sort, size_three) {
    std::vector<double> vect = std::vector<double>({3.0, 2.0, 1.0});
    std::vector<double> sorted = radixSort(vect);
    ASSERT_EQ(sorted, std::vector<double>({1, 2, 3}));
}

TEST(radix_sort, size_five) {
    std::vector<double> vect = std::vector<double>({3.0, 6.2, 1.0, 6.1, 7.0});
    std::vector<double> sorted = radixSort(vect);
    std::vector<double> checked = checkVector(vect);
    ASSERT_EQ(sorted, checked);
}

TEST(radix_sort, size_five_diff_radix) {
    std::vector<double> vect = std::vector<double>({3.7, 6.21, 1.0, 6.16, 7.2});
    std::vector<double> sorted = radixSort(vect);
    std::vector<double> checked = checkVector(vect);
    ASSERT_EQ(sorted, checked);
}

TEST(radix_sort, bigRadix) {
    std::vector<double> vect = std::vector<double>({3216.0, 6156.0, 145633.0, 6451.0, 71234.0});
    std::vector<double> sorted = radixSort(vect);
    std::vector<double> checked = checkVector(vect);
    ASSERT_EQ(sorted, checked);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
