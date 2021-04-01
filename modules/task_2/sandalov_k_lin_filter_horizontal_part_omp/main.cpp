// Copyright 2020 Sandalov Konstantin
#include <gtest/gtest.h>
#include <vector>
#include "../../modules/task_2/sandalov_k_lin_filter_horizontal_part_omp/lin_filter_horizontal_part_omp.h"


static const std::vector<float> init_arr {
    255, 5, 255, 254, 255,
    255, 255, 252, 255, 255,
    255, 254, 1, 252, 253,
    253, 255, 252, 255, 0,
    254, 3, 253, 255, 254
};

static const std::vector<uint8_t> res_arr {
    205, 172, 204, 254, 254,
    236, 204, 203, 234, 254,
    254, 222, 201, 203, 203,
    235, 203, 203, 203, 170,
    203, 171, 203, 235, 203
};

static const std::vector<float> correct_kernel {
    0.0751136, 0.123841, 0.0751136,
    0.123841, 0.20418, 0.123841,
    0.0751136, 0.123841, 0.0751136
};

TEST(Linear_Filter, Create_Filter_With_Even_Size) {
    ASSERT_ANY_THROW(my::createGaussianFilter(6, 1));
}

TEST(Linear_Filter, Create_Filter_With_Negative_Sigma) {
    ASSERT_ANY_THROW(my::createGaussianFilter(3, -1));
}

TEST(Linear_Filter, Create_Filter_With_Correct_Params) {
    std::vector<float> computedKernel;
    ASSERT_NO_THROW(computedKernel = my::createGaussianFilter(3, 1));
    ASSERT_EQ(computedKernel.size(), correct_kernel.size());
    for (size_t i = 0; i < computedKernel.size(); ++i) {
        ASSERT_NEAR(computedKernel[i], correct_kernel[i], 0.000001);
    }
}

TEST(Linear_Filter, Image_Processing_With_Incorrect_Img_Size) {
    std::vector<float> image(250, 0);
    std::vector<float> filter(9, 0);
    ASSERT_ANY_THROW(my::linearFilterSeq(image, filter, 10, 10, 3));
    ASSERT_ANY_THROW(my::linearFilterPar(image, filter, 10, 10, 3));
}

TEST(Linear_Filter, Image_Processing_With_Incorrect_Kernel_Size) {
    std::vector<float> image(250, 0);
    std::vector<float> filter(9, 0);
    ASSERT_ANY_THROW(my::linearFilterSeq(image, filter, 50, 5, 5));
    ASSERT_ANY_THROW(my::linearFilterPar(image, filter, 50, 5, 5));
}

TEST(Linear_Filter, Filter_Doesnt_Change_Blank_Image) {
    int64_t size{15};
    std::vector<float> blankImage(size * size, 255);
    auto kernel = my::createGaussianFilter(3, 1);
    auto resSeq = my::linearFilterSeq(blankImage, kernel, size, size, 3);
    for (size_t i = 0; i < blankImage.size(); ++i) {
        ASSERT_NEAR(blankImage[i], resSeq[i], 0.001);
    }
    auto resPar = my::linearFilterPar(blankImage, kernel, size, size, 3);
    for (size_t i = 0; i < blankImage.size(); ++i) {
        ASSERT_NEAR(blankImage[i], resPar[i], 0.001);
    }
    ASSERT_EQ(resSeq.size(), resPar.size());
    for (size_t i = 0; i < resSeq.size(); ++i) {
        ASSERT_NEAR(resSeq[i], resPar[i], 0.001);
    }
}

TEST(Linear_Filter, Filetr_Work_Correct) {
    auto kernel = my::createGaussianFilter(3, 1);
    auto resSeq = my::linearFilterSeq(init_arr, kernel, 5, 5, 3);
    for (size_t i = 0; i < init_arr.size(); ++i) {
        ASSERT_EQ(res_arr[i], static_cast<uint8_t>(resSeq[i]));
    }
    auto resPar = my::linearFilterPar(init_arr, kernel, 5, 5, 3);
    for (size_t i = 0; i < init_arr.size(); ++i) {
        ASSERT_EQ(res_arr[i], static_cast<uint8_t>(resPar[i]));
    }
    ASSERT_EQ(resSeq.size(), resPar.size());
    for (size_t i = 0; i < resSeq.size(); ++i) {
        ASSERT_EQ(static_cast<uint8_t>(resSeq[i]),
        static_cast<uint8_t>(resPar[i]));
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
