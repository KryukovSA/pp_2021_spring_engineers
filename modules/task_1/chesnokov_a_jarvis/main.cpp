// Copyright 2021 Chesnokov Artyom

#include <gtest/gtest.h>
#include <vector>
#include <list>

#include "jarvis.h"


TEST(JarvisTest, Simple_Check_No_Degenerates) {
  std::list<Point> pts =
  { 
    { 0,  3},
    {-2,  2},
    {-1,  2},
    { 1,  2},
    { 2,  2},
    { 2,  1},
    { 3,  1},
    { 0,  0},
    {-1, -1},
    { 1, -1},
    { 3, -1},
    { 1, -2}
  };
  
  std::vector<Point> res =
  {
    {-2,  2},
    { 0,  3},
    { 2,  2},
    { 3,  1},
    { 3, -1},
    { 1, -2},
    {-1, -1}
  };
  
  std::vector<Point> res2 = Jarvis::makeHull(pts);
  
  ASSERT_EQ(res.size(), res2.size()) << "Resulting CHs' sizes are even not equal!";
  
  for (size_t i = 0; i < res.size(); i++) {
    EXPECT_EQ(res2[i], res[i]) << "mismatch at i = " << i;
  }
}

TEST(JarvisTest, OK2) {
  SUCCEED();
}

TEST(JarvisTest, OK3) {
  SUCCEED();
}

TEST(JarvisTest, OK4) {
  SUCCEED();
}

TEST(JarvisTest, OK5) {
  SUCCEED();
}