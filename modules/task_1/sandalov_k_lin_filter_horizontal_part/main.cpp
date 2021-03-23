// Copyright 2020 Sandalov Konstantin
#include <gtest/gtest.h>
#include <vector>
#include "../../modules/task_1/sandalov_k_lin_filter_horizontal_part/lin_filter_horizontal_part.h"


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

static const float delta = 0.000001;

TEST(Parallel_Operations_OpenMP, Create_filter_with_even_size) {
    ASSERT_ANY_THROW(my::createGaussianFilter(6, 1));
}

TEST(Parallel_Operations_OpenMP, Create_filter_with_negative_sigma) {
    ASSERT_ANY_THROW(my::createGaussianFilter(3, -1));    
}

TEST(Parallel_Operations_OpenMP, Create_filter_with_correct_params) {
    std::vector<float> computedKernel;
    ASSERT_NO_THROW(computedKernel = my::createGaussianFilter(3, 1));
    ASSERT_EQ(computedKernel.size(), correct_kernel.size());
    for (size_t i = 0; i < computedKernel.size(); ++i) {
        ASSERT_NEAR(computedKernel[i], correct_kernel[i], 0.000001);
    }    
}

TEST(Parallel_Operations_OpenMP, Image_processing_with_incorrect_img_size) {
    std::vector<float> image (250, 0);
    std::vector<float> filter (9, 0);
    ASSERT_ANY_THROW(my::linearFilterSeq(image, filter, 10, 10, 3));
}

TEST(Parallel_Operations_OpenMP, Image_processing_with_incorrect_kernel_size) {
    std::vector<float> image (250, 0);
    std::vector<float> filter (9, 0);
    ASSERT_ANY_THROW(my::linearFilterSeq(image, filter, 50, 5, 4));
}

TEST(Parallel_Operations_OpenMP, Filter_doesnt_change_blank_image) {
    int64_t size{15};
    std::vector<float> blankImage (size * size, 255);
    auto kernel = my::createGaussianFilter(3, 1);
    auto res = my::linearFilterSeq(blankImage, kernel, size, size, 3);
    for (size_t i = 0; i < blankImage.size(); ++i) {
        ASSERT_NEAR(blankImage[i], res[i], 0.001);
    }
}

TEST(Parallel_Operations_OpenMP, Filetr_work_correct) {
    auto kernel = my::createGaussianFilter(3, 1);
    auto res = my::linearFilterSeq(init_arr, kernel, 5, 5, 3);
    for (size_t i = 0; i < init_arr.size(); ++i) {
        ASSERT_EQ(res_arr[i], static_cast<uint8_t>(res[i]));
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
