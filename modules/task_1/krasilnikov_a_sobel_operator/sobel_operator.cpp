// Copyright 2021 Krasilnikov Alexey
#include "../../modules/task_1/krasilnikov_a_sobel_operator/sobel_operator.h"

#include <cmath>
#include <algorithm>
#include <vector>

std::vector<unsigned char> ToMonochrome(
    const std::vector<unsigned char>& image, size_t height, size_t weight) {
    std::vector<unsigned char> ans;
    for (size_t i = 0; i < height * weight * 3; i += 3) {
        auto pixel = round(
                std::max(0., std::min(255., 0.2989 * image[i] + 0.5870 *
                                      image[i + 1] + 0.1140 * image[i + 2])));
        ans.push_back(static_cast<unsigned char>(pixel));
    }
    return ans;
}

std::vector<unsigned char> SobelOperator(
    const std::vector<unsigned char>& image, size_t height, size_t weight) {
    std::vector<unsigned char> ans(height * weight);
    for (size_t i = 1; i < height - 1; ++i) {
        for (size_t j = 1; j < weight - 1; ++j) {
            auto Gy = image[(i + 1) * height + (j - 1)] -
                      image[(i - 1) * height + (j - 1)] +
                      2 * image[(i + 1) * height + (j)] -
                      2 * image[(i - 1) * height + (j)] +
                      image[(i + 1) * height + (j + 1)] -
                      image[(i - 1) * height + (j + 1)];
            auto Gx = image[(i + 1) * height + (j + 1)] -
                      image[(i - 1) * height + (j - 1)] +
                      2 * image[(i) * height + (j + 1)] -
                      2 * image[(i) * height + (j - 1)] +
                      image[(i - 1) * height + (j + 1)] -
                      image[(i + 1) * height + (j - 1)];
            auto pixel = round(
                    std::max(0., std::min(255., sqrt(Gy * Gy + Gx * Gx))));
            ans[i * height + j] = static_cast<unsigned char>(pixel);
        }
    }
    return ans;
}
