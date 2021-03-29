// Copyright 2021 Schelyanskova Anastasiia

#include <gtest/gtest.h>

#include <vector>

#include "./radix_sort.h"

TEST(getRandomVector, wrong_size) { ASSERT_ANY_THROW(getRandomVector(-100)); }

TEST(getRandomVector, works) {
  std::vector<int> vect = getRandomVector(100);
  ASSERT_EQ(static_cast<int>(vect.size()), 100);
}

TEST(getRandomVector, no_exceptions) { ASSERT_NO_THROW(getRandomVector(100)); }

TEST(get_max_power, no_exceptions) {
  std::vector<int> vect = {1, 75, 87, 9, 400, 5};
  int power = 3;
  int max_power = get_max_power(vect);
  ASSERT_EQ(power, max_power);
}

TEST(radix_sort, correct_works) {
  std::vector<int> vect = {1, 7, 8, 9, 4, 5};
  std::vector<int> correctAnswer = {1, 4, 5, 7, 8, 9};
  std::vector<int> myAnswer = RadixSort(vect, 6);
  ASSERT_EQ(correctAnswer, myAnswer);
}

TEST(radix_sort, works_bubble) {
  std::vector<int> vect = {1, 17, 8, 95, 4, 51};
  std::vector<int> bubble = bubble_sort_vector(vect);
  std::vector<int> radix = RadixSort(vect, 6);
  ASSERT_EQ(bubble, radix);
}
//
//TEST(merge, works_with_sort) {
//  std::vector<int> vect2 = {103, 37, 9};
//  std::vector<int> vect1 = {3, 7, 1};
//  std::vector<int> sorted1 = RadixSort(vect1,3 );
//  std::vector<int> sorted2 = RadixSort(vect2,3 );
//  std::vector<int> sorted = Merge(sorted1, sorted2);
//  std::vector<int> correctAnswer = {1, 3, 7, 9, 37, 103};
//  ASSERT_EQ(sorted, correctAnswer);
//}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
