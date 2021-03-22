// Copyright 2021 Chesnokov Artyom

#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <random>

#include "../../../modules/task_1/chesnokov_a_jarvis/jarvis.h"

enum { LEFT, RIGHT, BEYOND, BEHIND, BETWEEN, ORIGIN, DESTINATION };

int classify(const Point& p0, const Point& p1, const Point& p2) {
  Point a = p1 - p0;
  Point b = p2 - p0;
  double sa = a.x * b.y - b.x * a.y;
  if (sa > 0.0)
    return LEFT;
  if (sa < 0.0)
    return RIGHT;
  if ((a.x * b.x < 0.0) || (a.y * b.y < 0.0))
    return BEHIND;
  if (a.length() < b.length())
    return BEYOND;
  if (p0 == p2)
    return ORIGIN;
  if (p1 == p2)
    return DESTINATION;
  return BETWEEN;
}

// checks simple predefined CH
TEST(JarvisTest, Simple_Check_No_Degenerates) {
  std::list<Point> pts = {
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

  std::vector<Point> res = {
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

// checks floating point precision problems with point closed to CH's edge
// and also degenerate case with 3 colinear points
TEST(JarvisTest, Degenerate_Case_Only_Extreme_Points) {
  std::list<Point> pts = {
    { 0,  3},
    { -0.001, 2.999},
    {-2,  2},
    {-1,  2},
    {-1.5, 0.5001},
    { 1,  2},
    { 2,  2},
    { 2,  1},
    { 3,  1},
    {1.6, 1.9},
    { 0,  0},
    {0.123, 0.321},
    {-1.05, 2.01},
    {2, -1.49999},
    {-0.999, -0.999 },
    {-1, -1},
    { 1, -1},
    { 3, -1},
    { 1, -2}
  };

  std::vector<Point> res = {
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

TEST(JarvisTest, Degenerate_Case_For_1_Point_CH_Is_This_One_Point) {
  std::list<Point> pt = { {0.322, 0.223} };
  std::vector<Point> res = Jarvis::makeHull(pt);

  EXPECT_EQ(res.size(), (size_t)1);
  EXPECT_EQ(pt.front(), res[0]);
}

TEST(JarvisTest, Degenerate_Case_For_2_Point_CH_Is_This_Two_Point) {
  std::list<Point> pt = { {0.322, 0.223}, {-0.322, -0.233} };
  std::vector<Point> res = Jarvis::makeHull(pt);
  std::vector<Point> exp = { {-0.322, -0.233}, {0.322, 0.223} };

  ASSERT_EQ(res.size(), (size_t)2);
  EXPECT_EQ(exp[0], res[0]);
  EXPECT_EQ(exp[1], res[1]);
}

TEST(JarvisTest, Degenerate_Case_From_Identical_Vertcies_Only_One_Is_Taken) {
  std::list<Point> pts = {
    { 0,  3}, { 0.0001,  2.9999},
    {-2,  2}, {-2,  2},
    {-1,  2}, {-1,  2},
    { 1,  2}, { 1,  2},
    { 2,  2}, { 2,  2},
    { 2,  1}, { 2,  1},
    { 3,  1}, { 2.999999,  0.9999999},
    { 0,  0}, { 0,  0},
    {-1, -1}, {-1, -1},
    { 1, -1}, { 1, -1},
    { 3, -1}, { 3, -1},
    { 1, -2}, { 0.9999, -1.999}
  };

  std::vector<Point> res = {
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

TEST(JarvisTest, Big_Check_1000_Random_Points_By_Def) {
  std::mt19937 generator;
  generator.seed(322);

  std::uniform_real_distribution<> distribution(0.0, 50.0);

  std::list<Point> pts;

  const int count = 1000;
  for (int i = 0; i < count; ++i)
    pts.emplace_back(distribution(generator), distribution(generator));

  std::vector<Point> res = Jarvis::makeHull(pts);
  for (size_t i = 1; i < res.size(); i++) {
    for (auto it = pts.begin(); it != pts.end(); it++) {
      int s = classify(res[i - 1], res[i], *it);
      EXPECT_TRUE(s == RIGHT || s == BEHIND || s == BEYOND || s == ORIGIN || s == DESTINATION);
    }
  }
}
