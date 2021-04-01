// Copyright 2021 Vizgalov Anton

#include <gtest/gtest.h>
#include <algorithm>

#include "./hoare_sort_simple_merge.h"

TEST(Hoare_Sort_Simple_Merge, Hoare_Sort_Empty_Vector) {
    std::vector<int> vec = getRandomVector(0);
    int lastIdx = static_cast<int>(vec.size() - 1);

    ASSERT_NO_THROW(hoareSort(&vec, 0, lastIdx));

    EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(Hoare_Sort_Simple_Merge, Hoare_Sort_Only_Positive_Numbers) {
    std::vector<int> vec = getRandomVector(100, 1);
    int lastIdx = static_cast<int>(vec.size() - 1);

    ASSERT_NO_THROW(hoareSort(&vec, 0, lastIdx));

    EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(Hoare_Sort_Simple_Merge, Hoare_Sort_All_Numbers_Small_Size) {
    std::vector<int> vec = getRandomVector(100);
    int lastIdx = static_cast<int>(vec.size() - 1);

    ASSERT_NO_THROW(hoareSort(&vec, 0, lastIdx));

    EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(Hoare_Sort_Simple_Merge, Hoare_Sort_All_Numbers_Big_Size) {
    std::vector<int> vec = getRandomVector(10000);
    int lastIdx = static_cast<int>(vec.size() - 1);

    ASSERT_NO_THROW(hoareSort(&vec, 0, lastIdx));

    EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(Hoare_Sort_Simple_Merge, Hoare_Sort_Already_Sorted) {
    std::vector<int> vec = getRandomVector(100, 2);
    int lastIdx = static_cast<int>(vec.size() - 1);

    ASSERT_NO_THROW(hoareSort(&vec, 0, lastIdx));

    EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(Hoare_Sort_Simple_Merge, Hoare_Sort_Worst_Case_Unsorted) {
    std::vector<int> vec = getRandomVector(100, 3);
    int lastIdx = static_cast<int>(vec.size() - 1);

    ASSERT_NO_THROW(hoareSort(&vec, 0, lastIdx));

    EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(Hoare_Sort_Simple_Merge, Merge_Left_Empty) {
    std::vector<int> vec = getRandomVector(100);
    int lastIdx = static_cast<int>(vec.size() - 1);
    hoareSort(&vec, 0, lastIdx);

    ASSERT_NO_THROW(merge(&vec, 0, 0, vec.size() - 1));

    EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(Hoare_Sort_Simple_Merge, Merge_Right_Empty) {
    std::vector<int> vec = getRandomVector(100);
    int lastIdx = static_cast<int>(vec.size() - 1);
    hoareSort(&vec, 0, lastIdx);

    ASSERT_NO_THROW(merge(&vec, 0, vec.size() - 1, vec.size() - 1));

    EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(Hoare_Sort_Simple_Merge, Merge_Same_Size) {
    std::vector<int> vec = getRandomVector(100);
    int lastIdx = static_cast<int>(vec.size() - 1);
    int midIdx = vec.size() / 2;
    hoareSort(&vec, 0, midIdx);
    hoareSort(&vec, midIdx + 1, lastIdx);

    ASSERT_NO_THROW(merge(&vec, 0, midIdx, vec.size() - 1));

    EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(Hoare_Sort_Simple_Merge, Merge_Different_Size) {
    std::vector<int> vec = getRandomVector(100);
    int lastIdx = static_cast<int>(vec.size() - 1);
    int divisionIdx = vec.size() / 8;
    hoareSort(&vec, 0, divisionIdx);
    hoareSort(&vec, divisionIdx + 1, lastIdx);

    ASSERT_NO_THROW(merge(&vec, 0, divisionIdx, vec.size() - 1));

    EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(Hoare_Sort_Simple_Merge, Merge_Large_Vectors) {
    std::vector<int> vec = getRandomVector(10000);
    int lastIdx = static_cast<int>(vec.size() - 1);
    int midIdx = vec.size() / 2;
    hoareSort(&vec, 0, midIdx);
    hoareSort(&vec, midIdx + 1, lastIdx);

    ASSERT_NO_THROW(merge(&vec, 0, midIdx, vec.size() - 1));

    EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(Hoare_Sort_Simple_Merge, Run_Hoare_Sort_Even_Size) {
    std::vector<int> vec = getRandomVector(100);

    ASSERT_NO_THROW(runHoareSort(&vec));

    EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(Hoare_Sort_Simple_Merge, Run_Hoare_Sort_Odd_Size) {
    std::vector<int> vec = getRandomVector(111);

    ASSERT_NO_THROW(runHoareSort(&vec));

    EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
