// Copyright 2021 Alekhin Denis
#include <gtest/gtest.h>
#include <math.h>
#include <omp.h>
#include "../../modules/task_3/alekhin_d_simpson_tbb/simpson.h"

#define PI 3.14159265

// y = x1( * x2 * ...)
std::function<double(std::vector<double>)> f1 = [](std::vector<double> arg) {
  double result = 1;
  for (size_t i = 0; i < arg.size(); i++) {
    result *= arg[i];
  }
  return result;
};

// y = x1( + x2 + ...)
std::function<double(std::vector<double>)> f2 = [](std::vector<double> arg) {
  double result = 0;
  for (size_t i = 0; i < arg.size(); i++) {
    result += arg[i];
  }
  return result;
};

// y = sin(x1)( + sin(x2) + ...)
std::function<double(std::vector<double>)> f3 = [](std::vector<double> arg) {
  double result = 0;
  for (size_t i = 0; i < arg.size(); i++) {
    result += sin(arg[i]);
  }
  return result;
};

TEST(Functions_Test, Function_F1_Test1) {
  std::vector<double> arg = { 1 };

  EXPECT_DOUBLE_EQ(1.0, f1(arg));
}

TEST(Functions_Test, Function_F1_Test2) {
  std::vector<double> arg = { 5, 20 };

  EXPECT_DOUBLE_EQ(100.0, f1(arg));
}

TEST(Functions_Test, Function_F1_Test3) {
  std::vector<double> arg = { 1, 2, -1, 20, 0.001, 20 };

  EXPECT_DOUBLE_EQ(-0.8, f1(arg));
}

TEST(Simpson_Method_TBB_Test, Simpson_TBB_Test1) {
  std::vector<std::pair<double, double>> scope = {
    std::make_pair(5, 10),
    std::make_pair(-10, -5),
    std::make_pair(0, 2) };

  EXPECT_NEAR(35.4, simpsonMethodTBB(scope, f3, 10), 0.1);
}

TEST(Simpson_Method_TBB_Test, Simpson_TBB_Test2) {
  std::vector<std::pair<double, double>> scope = {
    std::make_pair(0, 10) };

  EXPECT_NEAR(50, simpsonMethodTBB(scope, f1, 10), 1);
}

TEST(Simpson_Method_TBB_Test, Simpson_TBB_Test3) {
  std::vector<std::pair<double, double>> scope = {
    std::make_pair(-5, 5),
    std::make_pair(-5, 5) };

  EXPECT_NEAR(0, simpsonMethodTBB(scope, f2, 2), 1);
}

TEST(Simpson_Method_TBB_Test, Simpson_TBB_Test4) {
  std::vector<std::pair<double, double>> scope = {
    std::make_pair(0, 8) };

  EXPECT_NEAR(32, simpsonMethodTBB(scope, f2, 16), 1);
}

TEST(Simpson_Method_TBB_Test, Simpson_TBB_Test5) {
  std::vector<std::pair<double, double>> scope = {
    std::make_pair(0, 8),
    std::make_pair(0, 8) };

  EXPECT_NEAR(512, simpsonMethodTBB(scope, f2, 16), 1);
}

TEST(Simpson_Method_TBB_Test, Simpson_TBB_Test6) {
  std::vector<std::pair<double, double>> scope = {
    std::make_pair(0, 8),
    std::make_pair(0, 8) };

  EXPECT_NEAR(512, simpsonMethodTBB(scope, f2, 2), 1);
}

TEST(Simpson_Method_TBB_Test, Simpson_TBB_Test7) {
  std::vector<std::pair<double, double>> scope = {
    std::make_pair(0, 8),
    std::make_pair(0, 8) };

  EXPECT_NEAR(512, simpsonMethodTBB(scope, f2, 8), 1);
}

TEST(Simpson_Method_TBB_Test, Simpson_TBB_Test8) {
  std::vector<std::pair<double, double>> scope = {
    std::make_pair(-3, 12),
    std::make_pair(7, 9) };

  EXPECT_NEAR(375, simpsonMethodTBB(scope, f2, 20), 1);
}

TEST(Simpson_Method_TBB_Test, Simpson_TBB_Test9) {
  std::vector<std::pair<double, double>> scope = {
    std::make_pair(-3, 12),
    std::make_pair(7, 9),
    std::make_pair(0, 5) };

  EXPECT_NEAR(2250, simpsonMethodTBB(scope, f2, 1000), 1);
}

TEST(Simpson_Method_TBB_Test, Simpson_TBB_Test10) {
  std::vector<std::pair<double, double>> scope = {
    std::make_pair(5, 10),
    std::make_pair(-10, -5),
    std::make_pair(0, 2) };

  EXPECT_NEAR(35.4, simpsonMethodTBB(scope, f3, 10), 0.1);
}

TEST(Simpson_Method_TBB_Test, Simpson_TBB_Test11) {
  std::vector<std::pair<double, double>> scope = {
    std::make_pair(5, 10),
    std::make_pair(-10, -5) };

  EXPECT_NEAR(0, simpsonMethodTBB(scope, f3, 10), 1);
}

TEST(Simpson_Method_TBB_Test, Simpson_TBB_Test12) {
  std::vector<std::pair<double, double>> scope = {
    std::make_pair(5, 10) };

  EXPECT_NEAR(1.12, simpsonMethodTBB(scope, f3, 10), 0.1);
}

TEST(Simpson_Method_Test, Simpson_TBB_TimeTest) {
  std::vector<std::pair<double, double>> scope = {
    std::make_pair(5, 10),
    std::make_pair(-10, -5),
    std::make_pair(0, 2) };

  // double start = omp_get_wtime();
  double seqRes = simpsonMethod(scope, f3, 50);
  // double end = omp_get_wtime();
  // std::cout << "Sequential time: " << end - start << std::endl;

  // start = omp_get_wtime();
  double parRes = simpsonMethodTBB(scope, f3, 50);
  // end = omp_get_wtime();
  // std::cout << "Parallel time: " << end - start << std::endl;

  EXPECT_NEAR(seqRes, parRes, 1);
}
