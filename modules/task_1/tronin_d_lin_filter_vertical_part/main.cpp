// Copyright 2020 Tronin Dmitry
#include <gtest/gtest.h>
#include "../../modules/task_1/tronin_d_lin_filter_vertical_part/lin_filter_vertical_part.h"

TEST(LinearFilter, CalculateGaussFilter_even_size) {
    ASSERT_ANY_THROW(CalculateGaussFilter(4, 1.));
}

TEST(LinearFilter, CalculateGaussFilter_negative_sigma) {
    ASSERT_ANY_THROW(CalculateGaussFilter(5, -1.));
}

TEST(LinearFilter, CalculateGaussFilter) {
    auto filter = CalculateGaussFilter(3, 1.);
    std::vector<double> correct_filter{0.059, 0.097, 0.059,
                                       0.097, 0.159, 0.097,
                                       0.059, 0.097, 0.059};
    ASSERT_EQ(filter.size(), correct_filter.size()) << "Vectors x and y are of unequal length";
    for (size_t i = 0; i < filter.size(); ++i) {
        ASSERT_NEAR(filter[i], correct_filter[i], 1)
                            << "Filters are not equal at (" << i / 3 << ", " << i % 3 << ")";
    }
}

TEST(LinearFilter, Filter_throw_with_incorrect_size) {
    std::vector<uint8_t> image(400, 0);
    std::vector<double> filter(9, 0);
    ASSERT_ANY_THROW(ApplyFilter(filter, image, 40, 10, 4));
}

TEST(LinearFilter, Filter_doesnt_change_blank_image) {
    size_t size{10};
    std::vector<uint8_t> image(size * size, 255);
    auto result = ApplyFilter(CalculateGaussFilter(3, 1), image, size, size, 3);
    for (size_t i = 0; i < image.size(); ++i) {
        ASSERT_NEAR(image[i], result[i], 1)
                            << "Filters are not equal at (" << i / size << ", " << i % size << ")";
    }
}

TEST(LinearFilter, Filter_correct_values) {
    std::vector<uint8_t> initial_image{254, 255, 253, 255, 254, 255, 254, 255, 254, 254,
                                       255, 255, 252, 255, 255, 255, 251, 254, 255, 253,
                                       255, 254, 1, 252, 253, 255, 5, 255, 255, 253,
                                       253, 255, 252, 255, 255, 252, 255, 252, 252, 255,
                                       254, 253, 253, 255, 254, 255, 253, 255, 0, 252,
                                       255, 249, 7, 252, 252, 253, 255, 255, 1, 255,
                                       255, 255, 0, 255, 255, 255, 251, 2, 0, 254,
                                       253, 255, 0, 2, 0, 2, 0, 0, 255, 255,
                                       255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
                                       255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
    std::vector<uint8_t> correct_image{254, 254, 253, 254, 254, 254, 254, 254, 254, 253,
                                       254, 235, 222, 234, 254, 235, 222, 235, 254, 253,
                                       254, 222, 201, 222, 253, 223, 202, 223, 253, 253,
                                       253, 234, 222, 234, 254, 235, 223, 215, 222, 234,
                                       253, 234, 222, 235, 253, 253, 253, 203, 170, 203,
                                       253, 203, 171, 203, 253, 253, 235, 153, 120, 184,
                                       254, 184, 120, 134, 184, 184, 152, 101, 120, 204,
                                       254, 204, 140, 121, 140, 139, 120, 120, 172, 235,
                                       254, 235, 204, 185, 185, 185, 185, 204, 235, 255,
                                       255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
    auto result = ApplyFilter(CalculateGaussFilter(3, 1), initial_image, 10, 10, 3);
    for (size_t i = 0; i < initial_image.size(); ++i) {
        ASSERT_NEAR(correct_image[i], result[i], 1)
                            << "Filters are not equal at (" << i / 10 << ", "
                            << i % 10 << ")";
    }
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
