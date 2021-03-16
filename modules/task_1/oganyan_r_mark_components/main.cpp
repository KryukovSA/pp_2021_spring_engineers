// Copyright 2021 Oganyan Robert

#include <gtest/gtest.h>
#include <vector>
#include "../../modules/task_1/oganyan_r_mark_components/mark_components.h"


TEST(Comparing_to_a_sample, rectangle_image) {
    uint16_t width = 3;
    uint16_t height = 5;
    std::vector<uint16_t> source_image{
            0, 1, 1,
            0, 0, 0,
            1, 1, 1,
            0, 1, 0,
            0, 0, 0,
    };
    std::vector<uint16_t> result_image{
            0, 2, 2,
            0, 0, 0,
            3, 3, 3,
            0, 3, 0,
            0, 0, 0,
    };
    std::pair<std::vector<uint16_t>, uint16_t> res_image;
    ASSERT_NO_THROW(res_image = MarkComponents(source_image, height, width));
    ASSERT_EQ(res_image.second, 2);
}


TEST(Comparing_to_a_sample, square_image_1) {
    uint16_t width = 6;
    uint16_t height = 6;
    std::vector<uint16_t> source_image{
            0, 1, 0, 0, 0, 0,
            1, 1, 1, 0, 0, 1,
            0, 0, 0, 0, 1, 1,
            0, 1, 0, 1, 0, 0,
            1, 1, 1, 0, 0, 0,
            0, 0, 0, 0, 1, 1,
    };
    std::vector<uint16_t> result_image{
            0, 2, 0, 0, 0, 0,
            2, 2, 2, 0, 0, 3,
            0, 0, 0, 0, 3, 3,
            0, 3, 0, 3, 0, 0,
            3, 3, 3, 0, 0, 0,
            0, 0, 0, 0, 4, 4,
    };
    std::pair<std::vector<uint16_t>, uint16_t> res_image;
    ASSERT_NO_THROW(res_image = MarkComponents(source_image, height, width));
    ASSERT_EQ(res_image.second, 3);
}

TEST(Wrong_data, empty_image) {
    std::vector<uint16_t> source_image{
            0, 0, 1,
            1, 0, 1,
            0, 0, 0,
    };
    std::vector<uint16_t> result_image{
            0, 0, 2,
            3, 0, 2,
            0, 0, 0,
    };
    uint16_t width = 1;
    uint16_t height = 3;
    ASSERT_ANY_THROW(MarkComponents(source_image, height, width));
}

TEST(Wrong_data, wrong_width_and_height_1) {
    std::vector<uint16_t> source_image = {
            0, 1, 1,
            1, 0, 0,
            0, 0, 0,
    };
    std::vector<uint16_t> result_image = {
            0, 2, 2,
            2, 0, 0,
            0, 0, 0,
    };
    uint16_t width = 4;
    uint16_t height = 3;
    ASSERT_ANY_THROW(MarkComponents(source_image, height, width));
}

TEST(Wrong_data, wrong_width_and_height_2) {
    std::vector<uint16_t> source_image;
    std::vector<uint16_t> result_image;
    uint16_t width = 0;
    uint16_t height = 0;
    ASSERT_ANY_THROW(MarkComponents(source_image, height, width));
}


TEST(Comparing_to_a_sample, square_image_2) {
    uint16_t width = 5;
    uint16_t height = 5;
    std::vector<uint16_t> source_image{
            0, 1, 0, 1, 1,
            0, 0, 0, 1, 1,
            1, 0, 0, 0, 1,
            0, 0, 1, 1, 1,
            0, 0, 0, 0, 1,
    };
    std::vector<uint16_t> result_image{
            0, 2, 0, 3, 3,
            0, 0, 0, 4, 4,
            5, 0, 0, 0, 4,
            0, 0, 4, 4, 4,
            0, 0, 0, 0, 4,
    };
    std::pair<std::vector<uint16_t>, uint16_t> res_image;
    ASSERT_NO_THROW(res_image = MarkComponents(source_image, height, width));
    ASSERT_EQ(res_image.second, 3);
}

TEST(Wrong_data, wrong_img) {
    std::vector<uint16_t> source_image{
            0, 1, 1,
            0, 0, 1,
            1, 1,
    };
    std::vector<uint16_t> result_image{
            0, 2, 2,
            0, 0, 2,
            2, 2,
    };
    uint16_t width = 3;
    uint16_t height = 3;
    ASSERT_ANY_THROW(MarkComponents(source_image, height, width));
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
