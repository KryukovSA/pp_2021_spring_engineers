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
    std::vector<int> image1_decimal(height * width);
    image1_decimal[0] = 61; image1_decimal[1] = 2; image1_decimal[2] = 3; image1_decimal[3] = 4;
    image1_decimal[4] = 6; image1_decimal[5] = 8; image1_decimal[6] = 240; image1_decimal[7] = 2;
    image1_decimal[8] = 84; image1_decimal[9] = 6; image1_decimal[10] = 250; image1_decimal[11] = 3;
    image1_decimal[12] = 2; image1_decimal[13] = 8; image1_decimal[14] = 7; image1_decimal[15] = 3;
    image1_decimal[16] = 6;    image1_decimal[17] = 68; image1_decimal[18] = 2; image1_decimal[19] = 4;
    image1_decimal[20] = 3;    image1_decimal[21] = 9; image1_decimal[22] = 1; image1_decimal[23] = 4;
    image1_decimal[24] = 6;    image1_decimal[25] = 68; image1_decimal[26] = 2; image1_decimal[27] = 4;
    image1_decimal[28] = 3;    image1_decimal[29] = 9; image1_decimal[30] = 1; image1_decimal[31] = 4;
    image1_decimal[32] = 250;    image1_decimal[33] = 182; image1_decimal[34] = 90; image1_decimal[35] = 30;
    image1_decimal[36] = 23;    image1_decimal[37] = 4; image1_decimal[38] = 24; image1_decimal[39] = 1;
    image1_decimal[40] = 6;    image1_decimal[41] = 68; image1_decimal[42] = 2; image1_decimal[43] = 4;
    image1_decimal[44] = 3;    image1_decimal[45] = 9; image1_decimal[46] = 1; image1_decimal[47] = 4;
    image1_decimal[48] = 89;    image1_decimal[49] = 68; image1_decimal[50] = 5; image1_decimal[51] = 4;
    image1_decimal[52] = 3;    image1_decimal[53] = 9; image1_decimal[54] = 1; image1_decimal[55] = 4;
    image1_decimal[56] = 6;    image1_decimal[57] = 50; image1_decimal[58] = 2; image1_decimal[59] = 4;
    image1_decimal[60] = 3;    image1_decimal[61] = 9; image1_decimal[62] = 1; image1_decimal[63] = 4;
    ASSERT_NO_THROW(gaussianFilter(image1_decimal, height, width, radius, sigma));
}

TEST(Jacoby_Method, Test_check_gaussian_filter) {
    int radius = 1;
    float sigma = 5.0;
    int height = 8;
    int width = 8;
    std::vector<int> image1_decimal(height * width);
    std::vector<int> image2_decimal(height * width);
    std::vector<int> check(height * width);
    image1_decimal[0] = 61; image1_decimal[1] = 2; image1_decimal[2] = 3; image1_decimal[3] = 4;
    image1_decimal[4] = 6; image1_decimal[5] = 8; image1_decimal[6] = 240; image1_decimal[7] = 2;
    image1_decimal[8] = 84; image1_decimal[9] = 6; image1_decimal[10] = 250; image1_decimal[11] = 3;
    image1_decimal[12] = 2; image1_decimal[13] = 8; image1_decimal[14] = 7; image1_decimal[15] = 3;
    image1_decimal[16] = 6;    image1_decimal[17] = 68; image1_decimal[18] = 2; image1_decimal[19] = 4;
    image1_decimal[20] = 3;    image1_decimal[21] = 9; image1_decimal[22] = 1; image1_decimal[23] = 4;
    image1_decimal[24] = 6;    image1_decimal[25] = 68; image1_decimal[26] = 2; image1_decimal[27] = 4;
    image1_decimal[28] = 3;    image1_decimal[29] = 9; image1_decimal[30] = 1; image1_decimal[31] = 4;
    image1_decimal[32] = 250;    image1_decimal[33] = 182; image1_decimal[34] = 90; image1_decimal[35] = 30;
    image1_decimal[36] = 23;    image1_decimal[37] = 4; image1_decimal[38] = 24; image1_decimal[39] = 1;
    image1_decimal[40] = 6;    image1_decimal[41] = 68; image1_decimal[42] = 2; image1_decimal[43] = 4;
    image1_decimal[44] = 3;    image1_decimal[45] = 9; image1_decimal[46] = 1; image1_decimal[47] = 4;
    image1_decimal[48] = 89;    image1_decimal[49] = 68; image1_decimal[50] = 5; image1_decimal[51] = 4;
    image1_decimal[52] = 3;    image1_decimal[53] = 9; image1_decimal[54] = 1; image1_decimal[55] = 4;
    image1_decimal[56] = 6;    image1_decimal[57] = 50; image1_decimal[58] = 2; image1_decimal[59] = 4;
    image1_decimal[60] = 3;    image1_decimal[61] = 9; image1_decimal[62] = 1; image1_decimal[63] = 4;
    image2_decimal = gaussianFilter(image1_decimal, height, width, radius, sigma);
    check[0] = 46; check[1] = 51; check[2] = 30; check[3] = 30;
    check[4] = 5; check[5] = 58; check[6] = 58; check[7] = 55;
    check[8] = 42; check[9] = 53; check[10] = 38; check[11] = 30;
    check[12] = 5; check[13] = 31; check[14] = 31; check[15] = 29;
    check[16] = 37;    check[17] = 54; check[18] = 45; check[19] = 29;
    check[20] = 4;    check[21] = 4; check[22] = 5; check[23] = 3;
    check[24] = 93;    check[25] = 74; check[26] = 49; check[27] = 17;
    check[28] = 9;    check[29] = 8; check[30] = 6; check[31] = 4;
    check[32] = 94;    check[33] = 75; check[34] = 50; check[35] = 18;
    check[36] = 9;    check[37] = 8; check[38] = 6; check[39] = 4;
    check[40] = 111;    check[41] = 84; check[42] = 50; check[43] = 18;
    check[44] = 9;    check[45] = 8; check[46] = 6; check[47] = 4;
    check[48] = 43;    check[49] = 33; check[50] = 22; check[51] = 3;
    check[52] = 5;    check[53] = 4; check[54] = 4; check[55] = 3;
    check[56] = 40;    check[57] = 30; check[58] = 20; check[59] = 3;
    check[60] = 5;    check[61] = 4; check[62] = 4; check[63] = 3;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            ASSERT_EQ(image2_decimal[i * width + j], check[i * width + j]);
        }
    }
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
