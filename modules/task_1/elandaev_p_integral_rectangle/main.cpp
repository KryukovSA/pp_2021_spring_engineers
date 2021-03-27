// Copyright 2021 Elandaev Pavel
#include <gtest/gtest.h>
#include <math.h>
#include <iostream>
#include "../../modules/task_1/elandaev_p_integral_rectangle/rectangle.h"

double f1(double x) {
    double res = 10;
    return res;
}

double f2(double x) {
    double res = x * x;
    return res;
}

double f3(double x) {
    double res = sin(x) + 1;
    return res;
}

double f4(double x) {
    double res = sin(x) * cos(x);
    return res;
}

double f5(double x) {
    double res = sin(x) * cos(x) * x * x;
    return res;
}

TEST(INTEGRAL, Wrong_Interval) {
    double start = 6;
    double end = 4;
    double step = 0.001;
    ASSERT_ANY_THROW(RectangleIntegral(start, end, f1, step));
}

TEST(INTEGRAL, Step_Biggest) {
    double start = 2;
    double end = 4;
    double step = 4;
    ASSERT_ANY_THROW(RectangleIntegral(start, end, f1, step));
}

TEST(INTEGRAL, Step_negative) {
    double start = 2;
    double end = 40;
    double step = 0;
    ASSERT_ANY_THROW(RectangleIntegral(start, end, f1, step));
}

TEST(INTEGRAL, Integral_func_const) {
    double start = 2;
    double end = 4;
    double step = 0.001;
    ASSERT_EQ(20, RectangleIntegral(start, end, f1, step));
}

TEST(INTEGRAL, Integral_func_2) {
    double start = -2;
    double end = 4;
    double step = 0.001;
    ASSERT_NEAR(24, RectangleIntegral(start, end, f2, step), 0.01);
}

TEST(INTEGRAL, Integral_func_3) {
    double start = 0;
    double end = 12;
    double step = 0.001;
    ASSERT_NEAR(12.1561460, RectangleIntegral(start, end, f3, step), 0.01);
}

TEST(INTEGRAL, Integral_func_4) {
    double start = 0;
    double end = 12;
    double step = 0.001;
    ASSERT_NEAR(0.143955, RectangleIntegral(start, end, f4, step), 0.01);
}

TEST(INTEGRAL, Integral_func_4_v2) {
    double start = -4;
    double end = 3;
    double step = 0.001;
    ASSERT_NEAR(-0.276417, RectangleIntegral(start, end, f4, step), 0.01);
}

TEST(INTEGRAL, Integral_func_5) {
    double start = 0;
    double end = 12;
    double step = 0.0001;
    ASSERT_NEAR(-18.059156, RectangleIntegral(start, end, f5, step), 0.01);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
