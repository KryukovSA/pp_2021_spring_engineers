// Copyright 2021 Ekaterina Burmistrova
#include <gtest/gtest.h>
#include <vector>
#include <functional>
#include "./trapezoid_integral.h"

double integral(double x, double y = 1, double z = 1) {
    return (pow(x, 2));
}

double integral2(double x, double y, double z = 1) {
    return y/x;
}

double integral3(double x, double y, double z) {
    return x * y * z;
}

double integral4(double x, double y, double z = 1) {
    return pow(x, 2) + pow(y, 3);
}

double integral5(double x, double y, double z) {
    return x + y + z;
}

TEST(Parallel_Operations_OpenMP, Test_OneDim) {
    std::vector<std::pair<int, std::pair<int, int>>> vec;
    vec.push_back(std::make_pair(1, std::make_pair(2, 5)));
    // std::function<double(double)> func= pow(x, 2);
    double(*ptr1)(double, double, double) = integral;
    double par_int = SolveParallel(vec, ptr1);
    // int parallel_sum = getParallelOperations(vec, "+");
    ASSERT_NEAR(39.0, par_int, 0.6);
}

TEST(Parallel_Operations_OpenMP, Test_TwoDim) {
    std::vector<std::pair<int, std::pair<int, int>>> vec;
    vec.push_back(std::make_pair(1, std::make_pair(1, 2)));
    vec.push_back(std::make_pair(2, std::make_pair(2, 3)));
    // std::function<double(double)> func= pow(x, 2);
    double(*ptr2)(double, double, double) = integral2;
    double par_int = SolveParallel(vec, ptr2);
    // int parallel_sum = getParallelOperations(vec, "+");
    ASSERT_NEAR(1.73, par_int, 0.6);
}

TEST(Parallel_Operations_OpenMP, Test_ThreeDim) {
    std::vector<std::pair<int, std::pair<int, int>>> vec;
    vec.push_back(std::make_pair(1, std::make_pair(1, 2)));
    vec.push_back(std::make_pair(2, std::make_pair(2, 3)));
    vec.push_back(std::make_pair(3, std::make_pair(4, 5)));
    // std::function<double(double)> func= pow(x, 2);
    double(*ptr3)(double, double, double) = integral3;
    double par_int = SolveParallel(vec, ptr3);
    // int parallel_sum = getParallelOperations(vec, "+");
    ASSERT_NEAR(16.87, par_int, 0.6);
}

TEST(Parallel_Operations_OpenMP, Test_TwoDimSum) {
    std::vector<std::pair<int, std::pair<int, int>>> vec;
    vec.push_back(std::make_pair(1, std::make_pair(1, 3)));
    vec.push_back(std::make_pair(2, std::make_pair(2, 4)));
    // std::function<double(double)> func= pow(x, 2);
    double(*ptr4)(double, double, double) = integral4;
    double par_int = SolveParallelSum(vec, ptr4);
    // int parallel_sum = getParallelOperations(vec, "+");
    ASSERT_NEAR(68.67, par_int, 0.6);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
