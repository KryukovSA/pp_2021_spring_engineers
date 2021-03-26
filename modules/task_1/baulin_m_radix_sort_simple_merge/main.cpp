#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "./radix_sort.h"

TEST(radix_sort, works_2) {
    auto vect = std::vector<double>({1, 2});
    auto sorted = radix_sort(vect);
    ASSERT_EQ(sorted, std::vector<double>({1, 2}));
}

TEST(radix_sort, works_3) {
    auto vect = std::vector<double>({3, 1, 2});
    auto sorted = radix_sort(vect);
    ASSERT_EQ(sorted, std::vector<double>({1, 2, 3}));
}

TEST(radix_sort, works_5_without_negative) {
  auto vect = std::vector<double>({3.4, 3.545, 3.6, 3.54, 7});
  auto sorted = radix_sort(vect);
  ASSERT_EQ(sorted, std::vector<double>({3.4, 3.54, 3.545, 3.6, 7}));
}

TEST(radix_sort, works_5_with_negative) {
  auto vect = std::vector<double>({3.4, 3.545, 3.6, 3.54, 7, -1});
  auto sorted = radix_sort(vect);
  ASSERT_EQ(sorted, std::vector<double>({-1, 3.4, 3.54, 3.545, 3.6, 7}));
}

TEST(radix_sort, works_5_without_negative_with_error) {
  auto vect = std::vector<double>({3.5, 3.545, 3.6, 3.54, 7});
  auto sorted = radix_sort(vect);
  ASSERT_NE(sorted, std::vector<double>({3.4, 3.54, 3.545, 3.6, 7}));
}

TEST(radix_sort, works_5_with_negative_with_error) {
  auto vect = std::vector<double>({3.5, 3.545, 3.6, 3.54, 7, -1});
  auto sorted = radix_sort(vect);
  ASSERT_NE(sorted, std::vector<double>({-1, 3.4, 3.54, 3.545, 3.6, 7}));
}

TEST(radix_sort, works_6_without_negative) {
  auto vect = std::vector<double>({3.5, 3.4, 3.6, 3.54, 7, 1});
  auto sorted = radix_sort(vect);
  ASSERT_EQ(sorted, std::vector<double>({1, 3.4, 3.5, 3.54, 3.6, 7}));
}

TEST(radix_sort, works_6_with_negative) {
    auto vect = std::vector<double>({3.5, 3.4, 3.6, 3.54, 7, -1});
    auto sorted = radix_sort(vect);
    ASSERT_EQ(sorted, std::vector<double>({-1, 3.4, 3.5, 3.54, 3.6, 7}));
}

TEST(merge_radix_sort, works_6_with_negative) {
  auto vect1 = std::vector<double>({3.5, 3.4, 3.6});
  auto vect2 = std::vector<double>({3.54, 7, -1});
  auto sorted1 = radix_sort(vect1);
  auto sorted2 = radix_sort(vect2);
  auto sorted = merge(sorted1, sorted2);
  ASSERT_EQ(sorted, std::vector<double>({-1, 3.4, 3.5, 3.54, 3.6, 7}));
}

TEST(merge_radix_sort, works_6_with_negative_with_error) {
  auto vect1 = std::vector<double>({3.5, 3.4, 3.6});
  auto vect2 = std::vector<double>({3.54, 7, -1});
  auto sorted1 = radix_sort(vect1);
  auto sorted2 = radix_sort(vect2);
  auto sorted = merge(sorted1, sorted2);
  ASSERT_NE(sorted, std::vector<double>({3.4, -1, 3.5, 3.54, 3.6, 7}));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
