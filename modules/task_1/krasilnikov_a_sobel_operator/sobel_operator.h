// Copyright 2021 Krasilnikov Alexey
#ifndef MODULES_TASK_1_KRASILNIKOV_A_SOBEL_OPERATOR_SOBEL_OPERATOR_H_
#define MODULES_TASK_1_KRASILNIKOV_A_SOBEL_OPERATOR_SOBEL_OPERATOR_H_

#include <vector>

std::vector<unsigned char> ToMonochrome(
    const std::vector<unsigned char>& image, size_t height, size_t weight);

std::vector<unsigned char> SobelOperator(
    const std::vector<unsigned char>& image, size_t height, size_t weight);

#endif  // MODULES_TASK_1_KRASILNIKOV_A_SOBEL_OPERATOR_SOBEL_OPERATOR_H_
