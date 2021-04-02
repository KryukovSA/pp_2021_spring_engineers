// Copyright 2021 Krasilnikov Alexey
#include <gtest/gtest.h>
#include "../../modules/task_1/krasilnikov_a_sobel_operator/sobel_operator.h"

TEST(ToMonochrome, Arithmetic) {
    auto img = ToMonochrome({50, 100, 50}, 1, 1);
    ASSERT_EQ(1u, img.size());
    ASSERT_EQ(79, img[0]);

    img = ToMonochrome({50, 100, 150}, 1, 1);
    ASSERT_EQ(1u, img.size());
    ASSERT_EQ(91, img[0]);
}

TEST(ToMonochrome, Dimension) {
    auto img = ToMonochrome({0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0}, 2, 2);
    ASSERT_EQ(4u, img.size());
    ASSERT_EQ(0, img[0] + img[1] + img[2] + img[3]);

    img = ToMonochrome({0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0}, 1, 4);
    ASSERT_EQ(4u, img.size());
    ASSERT_EQ(0, img[0] + img[1] + img[2] + img[3]);

    img = ToMonochrome({255, 255, 255, 255, 255, 255,
                        255, 255, 255, 255, 255, 255}, 4, 1);
    ASSERT_EQ(4u, img.size());
    ASSERT_EQ(255 * 4, img[0] + img[1] + img[2] + img[3]);
}

TEST(SobelOperator, Smooth) {
    auto img = SobelOperator({0, 0, 0,
                              0, 0, 0,
                              0, 0, 0}, 3, 3);
    ASSERT_EQ(9u, img.size());
    ASSERT_EQ(0, img[4]);

    img = SobelOperator({255, 255, 255,
                         255, 255, 255,
                         255, 255, 255}, 3, 3);
    ASSERT_EQ(9u, img.size());
    ASSERT_EQ(0, img[4]);
}

TEST(SobelOperator, MaximumDifference) {
    auto img = SobelOperator({255, 0, 0,
                              255, 0, 0,
                              255, 0, 0}, 3, 3);
    ASSERT_EQ(9u, img.size());
    ASSERT_EQ(255, img[4]);

    img = SobelOperator({255, 255, 255,
                         0, 0, 0,
                         0, 0, 0}, 3, 3);
    ASSERT_EQ(9u, img.size());
    ASSERT_EQ(255, img[4]);

    img = SobelOperator({0, 0, 0,
                         0, 255, 0,
                         255, 255, 255}, 3, 3);
    ASSERT_EQ(9u, img.size());
    ASSERT_EQ(255, img[4]);
}

TEST(SobelOperator, Arithmetic) {
    auto img = SobelOperator({0, 10, 20,
                              70, 0, 30,
                              60, 50, 40}, 3, 3);
    ASSERT_EQ(9u, img.size());
    ASSERT_EQ(179, img[4]);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
