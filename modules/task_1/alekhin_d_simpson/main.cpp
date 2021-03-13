// Copyright 2021 Alekhin Denis
#include <gtest/gtest.h>
#include "../../modules/task_1/alekhin_d_simpson/simpson.h"

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

TEST(Input_Data_Test, Scope_Interval_Test1) {
  std::vector<std::pair<double, double>> scope =
  { std::make_pair<double, double>(1, 0) };
  
  EXPECT_ANY_THROW(simpsonMethod(scope, f1, 10));
}

TEST(Input_Data_Test, Scope_Interval_Test2) {
  std::vector<std::pair<double, double>> scope = {
    std::make_pair<double, double>(-1, 1),
    std::make_pair<double, double>(1, 0) };

  EXPECT_ANY_THROW(simpsonMethod(scope, f1, 10));
}

TEST(Input_Data_Test, Scope_Interval_Test3) {
  std::vector<std::pair<double, double>> scope;

  EXPECT_ANY_THROW(simpsonMethod(scope, f1, 10));
}

TEST(Input_Data_Test, Precision_Test) {
  std::vector<std::pair<double, double>> scope = 
  { std::make_pair<double, double>(0, 10) };

  EXPECT_ANY_THROW(simpsonMethod(scope, f1, 0));
}

TEST(Simpson_Method_Test, Simpson_Test1) {
  std::vector<std::pair<double, double>> scope = { 
    std::make_pair<double, double>(0, 10)};

  EXPECT_DOUBLE_EQ(50, simpsonMethod(scope, f1, 10));
}

TEST(Simpson_Method_Test, Simpson_Test2) {
  std::vector<std::pair<double, double>> scope = {
    std::make_pair<double, double>(-5, 5), 
    std::make_pair<double, double>(-5, 5) };

  EXPECT_DOUBLE_EQ(0, simpsonMethod(scope, f2, 2));
}

TEST(Simpson_Method_Test, Simpson_Test3) {
  std::vector<std::pair<double, double>> scope = {
    std::make_pair<double, double>(0, 8) };

  EXPECT_DOUBLE_EQ(32, simpsonMethod(scope, f2, 16));
}

TEST(Simpson_Method_Test, Simpson_Test4) {
  std::vector<std::pair<double, double>> scope = {
    std::make_pair<double, double>(0, 8),
    std::make_pair<double, double>(0, 8) };

  EXPECT_DOUBLE_EQ(64, simpsonMethod(scope, f2, 16));
}
