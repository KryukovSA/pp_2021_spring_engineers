// Copyright 2021 Kustova Anastasiya
#include <gtest/gtest.h>
#include <math.h>
#include<vector>
#include<iostream>
#include"./filter_gaussa_block.h"

TEST(Jacoby_Method, Test_1) {
    int radius = 1;
    float sigma = 5.0;
    int height = 8;
    int width = 8;
    int ** image1_decimal = new int*[height];
    int ** image2_decimal = new int*[height];
    int ** check = new int*[height];
    for (int i = 0; i < height; i++) {
        image1_decimal[i] = new int[width];
        image2_decimal[i] = new int[width];
        check[i] = new int[width];
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
    image2_decimal = gaussianFilter(image1_decimal, height, width, radius, sigma);
    check[0][0] = 46; check[0][1] = 51; check[0][2] = 30; check[0][3] = 30;
    check[0][4] = 5; check[0][5] = 58; check[0][6] = 58; check[0][7] = 55;
    check[1][0] = 42; check[1][1] = 53; check[1][2] = 38; check[1][3] = 30;
    check[1][4] = 5; check[1][5] = 31; check[1][6] = 31; check[1][7] = 29;
    check[2][0] = 37;    check[2][1] = 54; check[2][2] = 45; check[2][3] = 29;
    check[2][4] = 4;    check[2][5] = 4; check[2][6] = 5; check[2][7] = 3;
    check[3][0] = 93;    check[3][1] = 74; check[3][2] = 49; check[3][3] = 17;
    check[3][4] = 9;    check[3][5] = 8; check[3][6] = 6; check[3][7] = 4;
    check[4][0] = 94;    check[4][1] = 75; check[4][2] = 50; check[4][3] = 18;
    check[4][4] = 9;    check[4][5] = 8; check[4][6] = 6; check[4][7] = 4;
    check[5][0] = 111;    check[5][1] = 84; check[5][2] = 50; check[5][3] = 18;
    check[5][4] = 9;    check[5][5] = 8; check[5][6] = 6; check[5][7] = 4;
    check[6][0] = 43;    check[6][1] = 33; check[6][2] = 22; check[6][3] = 3;
    check[6][4] = 5;    check[6][5] = 4; check[6][6] = 4; check[6][7] = 3;
    check[7][0] = 40;    check[7][1] = 30; check[7][2] = 20; check[7][3] = 3;
    check[7][4] = 5;    check[7][5] = 4; check[7][6] = 4; check[7][7] = 3;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            ASSERT_EQ(image2_decimal[i][j], check[i][j]);
        }
    }
}
TEST(Jacoby_Method, Test_2) {
    int radius = 1;
    float sigma = 5.0;
    int height = 8;
    int width = 8;
    int ** image1_decimal = new int*[height];
    int ** image2_decimal = new int*[height];
    int ** check = new int*[height];
    for (int i = 0; i < height; i++) {
        image1_decimal[i] = new int[width];
        image2_decimal[i] = new int[width];
        check[i] = new int[width];
    }
    image1_decimal[0][0] = 255; image1_decimal[0][1] = 255; image1_decimal[0][2] = 255; image1_decimal[0][3] = 255;
    image1_decimal[0][4] = 255; image1_decimal[0][5] = 255; image1_decimal[0][6] = 255; image1_decimal[0][7] = 255;
    image1_decimal[1][0] = 255; image1_decimal[1][1] = 255; image1_decimal[1][2] = 255; image1_decimal[1][3] = 255;
    image1_decimal[1][4] = 255; image1_decimal[1][5] = 255; image1_decimal[1][6] = 255; image1_decimal[1][7] = 255;
    image1_decimal[2][0] = 255; image1_decimal[2][1] = 255; image1_decimal[2][2] = 255; image1_decimal[2][3] = 255;
    image1_decimal[2][4] = 255; image1_decimal[2][5] = 255; image1_decimal[2][6] = 255; image1_decimal[2][7] = 255;
    image1_decimal[3][0] = 255; image1_decimal[3][1] = 255; image1_decimal[3][2] = 255; image1_decimal[3][3] = 255;
    image1_decimal[3][4] = 255; image1_decimal[3][5] = 255; image1_decimal[3][6] = 255; image1_decimal[3][7] = 255;
    image1_decimal[4][0] = 255; image1_decimal[4][1] = 255; image1_decimal[4][2] = 255; image1_decimal[4][3] = 0;
    image1_decimal[4][4] = 255; image1_decimal[4][5] = 255; image1_decimal[4][6] = 255; image1_decimal[4][7] = 255;
    image1_decimal[5][0] = 255; image1_decimal[5][1] = 255; image1_decimal[5][2] = 255; image1_decimal[5][3] = 255;
    image1_decimal[5][4] = 255; image1_decimal[5][5] = 255; image1_decimal[5][6] = 255; image1_decimal[5][7] = 255;
    image1_decimal[6][0] = 255; image1_decimal[6][1] = 255; image1_decimal[6][2] = 255; image1_decimal[6][3] = 255;
    image1_decimal[6][4] = 255; image1_decimal[6][5] = 255; image1_decimal[6][6] = 255; image1_decimal[6][7] = 255;
    image1_decimal[7][0] = 255; image1_decimal[7][1] = 255; image1_decimal[7][2] = 255; image1_decimal[7][3] = 255;
    image1_decimal[7][4] = 255; image1_decimal[7][5] = 255; image1_decimal[7][6] = 255; image1_decimal[7][7] = 255;
    image2_decimal = gaussianFilter(image1_decimal, height, width, radius, sigma);
    check[0][0] = 254; check[0][1] = 254; check[0][2] = 254; check[0][3] = 254;
    check[0][4] = 254; check[0][5] = 254; check[0][6] = 254; check[0][7] = 254;
    check[1][0] = 254; check[1][1] = 254; check[1][2] = 254; check[1][3] = 254;
    check[1][4] = 254; check[1][5] = 254; check[1][6] = 254; check[1][7] = 254;
    check[2][0] = 254; check[2][1] = 254; check[2][2] = 254; check[2][3] = 254;
    check[2][4] = 254; check[2][5] = 254; check[2][6] = 254; check[2][7] = 254;
    check[3][0] = 254; check[3][1] = 254; check[3][2] = 227; check[3][3] = 226;
    check[3][4] = 227; check[3][5] = 254; check[3][6] = 254; check[3][7] = 254;
    check[4][0] = 254; check[4][1] = 254; check[4][2] = 226; check[4][3] = 225;
    check[4][4] = 226; check[4][5] = 254; check[4][6] = 254; check[4][7] = 254;
    check[5][0] = 254; check[5][1] = 254; check[5][2] = 227; check[5][3] = 226;
    check[5][4] = 227; check[5][5] = 254; check[5][6] = 254; check[5][7] = 254;
    check[6][0] = 254; check[6][1] = 254; check[6][2] = 254; check[6][3] = 254;
    check[6][4] = 254; check[6][5] = 254; check[6][6] = 254; check[6][7] = 254;
    check[7][0] = 254; check[7][1] = 254; check[7][2] = 254; check[7][3] = 254;
    check[7][4] = 254; check[7][5] = 254; check[7][6] = 254; check[7][7] = 254;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            ASSERT_EQ(image2_decimal[i][j], check[i][j]);
        }
    }
}

TEST(Jacoby_Method, Test_3) {
    int radius = 2;
    float sigma = 3.0;
    int height = 8;
    int width = 8;
    int ** image1_decimal = new int*[height];
    int ** image2_decimal = new int*[height];
    int ** check = new int*[height];
    for (int i = 0; i < height; i++) {
        image1_decimal[i] = new int[width];
        image2_decimal[i] = new int[width];
        check[i] = new int[width];
    }
    image1_decimal[0][0] = 255; image1_decimal[0][1] = 255; image1_decimal[0][2] = 255; image1_decimal[0][3] = 255;
    image1_decimal[0][4] = 255; image1_decimal[0][5] = 255; image1_decimal[0][6] = 255; image1_decimal[0][7] = 255;
    image1_decimal[1][0] = 255; image1_decimal[1][1] = 255; image1_decimal[1][2] = 255; image1_decimal[1][3] = 255;
    image1_decimal[1][4] = 255; image1_decimal[1][5] = 255; image1_decimal[1][6] = 255; image1_decimal[1][7] = 255;
    image1_decimal[2][0] = 255; image1_decimal[2][1] = 255; image1_decimal[2][2] = 255; image1_decimal[2][3] = 255;
    image1_decimal[2][4] = 255; image1_decimal[2][5] = 255; image1_decimal[2][6] = 255; image1_decimal[2][7] = 255;
    image1_decimal[3][0] = 255; image1_decimal[3][1] = 255; image1_decimal[3][2] = 255; image1_decimal[3][3] = 255;
    image1_decimal[3][4] = 255; image1_decimal[3][5] = 255; image1_decimal[3][6] = 255; image1_decimal[3][7] = 255;
    image1_decimal[4][0] = 255; image1_decimal[4][1] = 255; image1_decimal[4][2] = 255; image1_decimal[4][3] = 0;
    image1_decimal[4][4] = 255; image1_decimal[4][5] = 255; image1_decimal[4][6] = 255; image1_decimal[4][7] = 255;
    image1_decimal[5][0] = 255; image1_decimal[5][1] = 255; image1_decimal[5][2] = 255; image1_decimal[5][3] = 255;
    image1_decimal[5][4] = 255; image1_decimal[5][5] = 255; image1_decimal[5][6] = 255; image1_decimal[5][7] = 255;
    image1_decimal[6][0] = 255; image1_decimal[6][1] = 255; image1_decimal[6][2] = 255; image1_decimal[6][3] = 255;
    image1_decimal[6][4] = 255; image1_decimal[6][5] = 255; image1_decimal[6][6] = 255; image1_decimal[6][7] = 255;
    image1_decimal[7][0] = 255; image1_decimal[7][1] = 255; image1_decimal[7][2] = 255; image1_decimal[7][3] = 255;
    image1_decimal[7][4] = 255; image1_decimal[7][5] = 255; image1_decimal[7][6] = 255; image1_decimal[7][7] = 255;
    image2_decimal = gaussianFilter(image1_decimal, height, width, radius, sigma);
    check[0][0] = 255; check[0][1] = 255; check[0][2] = 255; check[0][3] = 255;
    check[0][4] = 255; check[0][5] = 255; check[0][6] = 255; check[0][7] = 255;
    check[1][0] = 255; check[1][1] = 255; check[1][2] = 255; check[1][3] = 255;
    check[1][4] = 255; check[1][5] = 255; check[1][6] = 255; check[1][7] = 255;
    check[2][0] = 255; check[2][1] = 246; check[2][2] = 245; check[2][3] = 244;
    check[2][4] = 245; check[2][5] = 246; check[2][6] = 255; check[2][7] = 255;
    check[3][0] = 255; check[3][1] = 245; check[3][2] = 243; check[3][3] = 243;
    check[3][4] = 243; check[3][5] = 245; check[3][6] = 255; check[3][7] = 255;
    check[4][0] = 255; check[4][1] = 244; check[4][2] = 243; check[4][3] = 242;
    check[4][4] = 243; check[4][5] = 244; check[4][6] = 255; check[4][7] = 255;
    check[5][0] = 255; check[5][1] = 245; check[5][2] = 243; check[5][3] = 243;
    check[5][4] = 243; check[5][5] = 245; check[5][6] = 255; check[5][7] = 255;
    check[6][0] = 255; check[6][1] = 246; check[6][2] = 245; check[6][3] = 244;
    check[6][4] = 245; check[6][5] = 246; check[6][6] = 255; check[6][7] = 255;
    check[7][0] = 255; check[7][1] = 255; check[7][2] = 255; check[7][3] = 255;
    check[7][4] = 255; check[7][5] = 255; check[7][6] = 255; check[7][7] = 255;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            ASSERT_EQ(image2_decimal[i][j], check[i][j]);
        }
    }
}

TEST(Jacoby_Method, Test_creating_Gaussian_Kernel) {
    int radius = 1;
    float sigma = 5.0;
    std::vector<float> kernel1(9);
    kernel1[0] = static_cast<float>(0.109629683);
    kernel1[1] = static_cast<float>(0.111844353);
    kernel1[2] = static_cast<float>(0.109629683);
    kernel1[3] = static_cast<float>(0.111844353);
    kernel1[4] = static_cast<float>(0.114103757);
    kernel1[5] = static_cast<float>(0.111844353);
    kernel1[6] = static_cast<float>(0.109629683);
    kernel1[7] = static_cast<float>(0.111844353);
    kernel1[8] = static_cast<float>(0.109629683);
    std::vector<float> kernel2 = createGaussianKernel(radius, sigma);
    for (int i = 0; i < 9; i++) {
        ASSERT_NEAR(kernel1[i], kernel2[i], 0.001);
    }
}
TEST(Jacoby_Method, Test_check_Clamp) {
    int val1 = -1;
    ASSERT_EQ(Clamp(val1, 0, 255), 0);
    ASSERT_EQ(Clamp(val1, -5, 30), -1);
    ASSERT_EQ(Clamp(val1, -5, -3), -3);
}
