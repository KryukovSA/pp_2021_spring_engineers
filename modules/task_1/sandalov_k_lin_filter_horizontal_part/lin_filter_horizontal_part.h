// Copyright 2020 Sandalov Konstantin
#ifndef MODULES_TASK_1_SANDALOV_K_LIN_FILTER_HORIZONTAL_PART_LIN_FILTER_HORIZONTAL_PART_H_
#define MODULES_TASK_1_SANDALOV_K_LIN_FILTER_HORIZONTAL_PART_LIN_FILTER_HORIZONTAL_PART_H_

#include <vector>
#include <cstdint>


namespace my {
    std::vector<float> createGaussianFilter(int64_t N, double sigma);
    std::vector<float> linearFilterSeq(const std::vector<float>& srcImg,
        const std::vector<float>& kernel, int64_t N, int64_t M, int64_t K);
}

#endif  // MODULES_TASK_1_SANDALOV_K_LIN_FILTER_HORIZONTAL_PART_LIN_FILTER_HORIZONTAL_PART_H_
