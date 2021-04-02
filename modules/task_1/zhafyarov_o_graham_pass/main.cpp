// Copyright 2021 Zhafyarov Oleg
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "./graham_pass.h"

TEST(Sequential, Test1) {
  std::vector<point> vec = {{1, 5}, {4, 8}, {8, 2}, {9, 3}, {1, 8}, {7, 7}};
  std::vector<size_t> result;
  int count = 0;
  result = GrahamPass(vec, &count);
  std::vector<size_t> compare = { 0, 2, 3, 5, 1, 4 };
  ASSERT_EQ(compare, result);
}

TEST(Sequential, Test2) {
  std::vector<point> vec = { {1, 5}, {4, 8}, {8, 2}, {9, 3}, {1, 8},
    {7, 7}, {5, 5}, {2, 1}, {11, 9} };
  std::vector<size_t> result;
  int count = 0;
  result = GrahamPass(vec, &count);
  std::vector<size_t> compare = { 0, 7, 2, 3, 8, 4 };
  ASSERT_EQ(compare, result);
}

TEST(Sequential, Test3) {
  std::vector<point> vec = { {1, 1}, {1, 4}, {4, 1}, {4, 4}, {2, 2}};
  std::vector<size_t> result;
  int count = 0;
  int count_tmp = 4;
  result = GrahamPass(vec, &count);
  ASSERT_EQ(count, count_tmp);
}

TEST(Sequential, Test4) {
  ASSERT_ANY_THROW(std::vector<point> vec = RandomVector(-1));
}

TEST(Sequential, Test5) {
  int size = 50;
  int count = 0;
  std::vector<point> vec = RandomVector(size);
  std::vector<size_t> result;
  result = GrahamPass(vec, &count);
  ASSERT_GT(count, 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
