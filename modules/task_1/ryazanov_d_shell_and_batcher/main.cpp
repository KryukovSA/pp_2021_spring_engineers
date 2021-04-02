// Copyright 2021 Dmitry Ryazanov
#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include "./ryazanov_d_shell_and_batcher.h"

TEST(getRandomVector, no_exceptions) { ASSERT_NO_THROW(getRandomVector(100)); }

TEST(getRandomVector, wrong_size) { ASSERT_ANY_THROW(getRandomVector(-100)); }

TEST(getRandomVector, works) {
  auto vect = getRandomVector(100);
  ASSERT_EQ(static_cast<int>(vect.size()), 100);
}

TEST(Shell_and_Batcher_sort, no_exceptions) {
  auto vect = getRandomVector(100);
  ASSERT_NO_THROW(SortShell(vect));
}

TEST(Shell_and_Batcher_sort, works_size_two) {
  auto vect = std::vector<int>({2, 1});
  print(vect);
  auto res = SortShell(vect);
  print(res);
  ASSERT_EQ(res, std::vector<int>({1, 2}));
}

TEST(Shell_and_Batcher_sort, works_size_4) {
  std::vector<int> vect = getRandomVector(4);
  print(vect);
  auto res = BatcherSort(vect);
  print(res);
}

TEST(Shell_and_Batcher_sort, works_random_size_100) {
  auto vect = getRandomVector(100);
  auto sorted = SortShell(vect);
  std::sort(vect.begin(), vect.end());
  ASSERT_EQ(vect, sorted);
}

TEST(Shell_and_Batcher_sort, works_random_vec_Shell_and_Batcher) {
  auto vect = getRandomVector(100);
  auto res1 = SortShell(vect);
  auto res2 = BatcherSort(vect);
  std::sort(vect.begin(), vect.end());
  ASSERT_EQ(res1, res2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
