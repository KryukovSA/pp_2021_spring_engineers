// Copyright 2021 Kustova Anastasiya
#include <gtest/gtest.h>
#include <math.h>
#include<vector>
#include<iostream>
#include"./filter_gaussa_block.h"

TEST(Jacoby_Method, Test_can_gaussian_filter) {
    int radius = 1;
    float sigma = 5.0;
    int height = 8;
    int width = 8;
    int ** image1_decimal = new int*[height];
    for (int i = 0; i < height; i++) {
        image1_decimal[i] = new int[width];
    }
    image1_decimal[0][0] = 61; image1_decimal[0][1] = 2; image1_decimal[0][2] = 3; image1_decimal[0][3] = 4;
    image1_decimal[0][4] = 6; image1_decimal[0][5] = 8; image1_decimal[0][6] = 240; image1_decimal[0][7] = 2;
    image1_decimal[1][0] = 84; image1_decimal[1][1] = 6; image1_decimal[1][2] = 250; image1_decimal[1][3] = 3;
    image1_decimal[1][4] = 2; image1_decimal[1][5] = 8; image1_decimal[1][6] = 7; image1_decimal[1][7] = 3;
    image1_decimal[2][0] = 6;    image1_decimal[2][1] = 68; image1_decimal[2][2] = 2; image1_decimal[2][3] = 4;
    image1_decimal[2][4] = 3;    image1_decimal[2][5] = 9; image1_decimal[2][6] = 1; image1_decimal[2][7] = 4;
    image1_decimal[3][0] = 6;    image1_decimal[3][1] = 68; image1_decimal[3][2] = 2; image1_decimal[3][3] = 4;
    image1_decimal[3][4] = 3;    image1_decimal[3][5] = 9; image1_decimal[3][6] = 1; image1_decimal[3][7] = 4;
    image1_decimal[4][0] = 250;    image1_decimal[4][1] = 182; image1_decimal[4][2] = 90; image1_decimal[4][3] = 30;
    image1_decimal[4][4] = 23;    image1_decimal[4][5] = 4; image1_decimal[4][6] = 24; image1_decimal[4][7] = 1;
    image1_decimal[5][0] = 6;    image1_decimal[5][1] = 68; image1_decimal[5][2] = 2; image1_decimal[5][3] = 4;
    image1_decimal[5][4] = 3;    image1_decimal[5][5] = 9; image1_decimal[5][6] = 1; image1_decimal[5][7] = 4;
    image1_decimal[6][0] = 89;    image1_decimal[6][1] = 68; image1_decimal[6][2] = 5; image1_decimal[6][3] = 4;
    image1_decimal[6][4] = 3;    image1_decimal[6][5] = 9; image1_decimal[6][6] = 1; image1_decimal[6][7] = 4;
    image1_decimal[7][0] = 6;    image1_decimal[7][1] = 50; image1_decimal[7][2] = 2; image1_decimal[7][3] = 4;
    image1_decimal[7][4] = 3;    image1_decimal[7][5] = 9; image1_decimal[7][6] = 1; image1_decimal[7][7] = 4;
    ASSERT_NO_THROW(gaussianFilter(image1_decimal, height, width, radius, sigma));
}
TEST(Jacoby_Method, Test_can_calculate_NewPixelColor) {
    int radius = 1;
    float sigma = 5.0;
    int height = 8;
    int width = 8;
    int ** image1_decimal = new int*[height];
    for (int i = 0; i < height; i++) {
        image1_decimal[i] = new int[width];
    }
    image1_decimal[0][0] = 61; image1_decimal[0][1] = 2; image1_decimal[0][2] = 3; image1_decimal[0][3] = 4;
    image1_decimal[0][4] = 6; image1_decimal[0][5] = 8; image1_decimal[0][6] = 240; image1_decimal[0][7] = 2;
    image1_decimal[1][0] = 84; image1_decimal[1][1] = 6; image1_decimal[1][2] = 250; image1_decimal[1][3] = 3;
    image1_decimal[1][4] = 2; image1_decimal[1][5] = 8; image1_decimal[1][6] = 7; image1_decimal[1][7] = 3;
    image1_decimal[2][0] = 6;    image1_decimal[2][1] = 68; image1_decimal[2][2] = 2; image1_decimal[2][3] = 4;
    image1_decimal[2][4] = 3;    image1_decimal[2][5] = 9; image1_decimal[2][6] = 1; image1_decimal[2][7] = 4;
    image1_decimal[3][0] = 6;    image1_decimal[3][1] = 68; image1_decimal[3][2] = 2; image1_decimal[3][3] = 4;
    image1_decimal[3][4] = 3;    image1_decimal[3][5] = 9; image1_decimal[3][6] = 1; image1_decimal[3][7] = 4;
    image1_decimal[4][0] = 250;    image1_decimal[4][1] = 182; image1_decimal[4][2] = 90; image1_decimal[4][3] = 30;
    image1_decimal[4][4] = 23;    image1_decimal[4][5] = 4; image1_decimal[4][6] = 24; image1_decimal[4][7] = 1;
    image1_decimal[5][0] = 6;    image1_decimal[5][1] = 68; image1_decimal[5][2] = 2; image1_decimal[5][3] = 4;
    image1_decimal[5][4] = 3;    image1_decimal[5][5] = 9; image1_decimal[5][6] = 1; image1_decimal[5][7] = 4;
    image1_decimal[6][0] = 89;    image1_decimal[6][1] = 68; image1_decimal[6][2] = 5; image1_decimal[6][3] = 4;
    image1_decimal[6][4] = 3;    image1_decimal[6][5] = 9; image1_decimal[6][6] = 1; image1_decimal[6][7] = 4;
    image1_decimal[7][0] = 6;    image1_decimal[7][1] = 50; image1_decimal[7][2] = 2; image1_decimal[7][3] = 4;
    image1_decimal[7][4] = 3;    image1_decimal[7][5] = 9; image1_decimal[7][6] = 1; image1_decimal[7][7] = 4;
    int size = 2 * radius + 1;
    std::vector<float> kernel(size * size);
    kernel = createGaussianKernel(radius, sigma);
    ASSERT_NO_THROW(calculateNewPixelColor(image1_decimal, width, height, 3, 3, radius, kernel));
}
TEST(Jacoby_Method, Test_can_Clamp) {
    int val1 = -1;
    ASSERT_NO_THROW(Clamp(val1, 0, 255));
}
TEST(Jacoby_Method, Test_check_Clamp) {
    int val1 = -1;
    ASSERT_EQ(Clamp(val1, 0, 255), 0);
    ASSERT_EQ(Clamp(val1, -5, 30), -1);
    ASSERT_EQ(Clamp(val1, -5, -3), -3);
}

TEST(Jacoby_Method, Can_creating_Gaussian_Kernel) {
    int radius = 1;
    float sigma = 5.0;
    ASSERT_NO_THROW(createGaussianKernel(radius, sigma));
}
