// Copyright 2021 Kustova Anastasiya
#include <math.h>
#include <omp.h>
#include <iostream>
#include <vector>
#include <tuple>
#include "../../../modules/task_2/kustova_a_gauss_omp/filter_gaussa_block.h"

std::vector<int> gaussianFilter(const std::vector<int> & img, int width,
    int height, int radius, float sigma, int count_thread) {
    std::vector<int> resultImage(height * width);
    int size = 2 * radius + 1;
    std::vector<float> kernel(size * size);
    int l = 0;
    int k = 0;
    kernel = createGaussianKernel(radius, sigma);
    std::vector<std::vector<int>> array;
    int grid_size = ceil(static_cast<double>(sqrt(count_thread)));
    int block_height = height / grid_size;
    int block_width = width / grid_size;
    while (l < height) {
        k = 0;
        while (k < width) {
            std::vector<int> tup = { l, k };
            array.push_back(tup);
            k += block_width;
        }
        l += block_height;
    }
#pragma omp parallel num_threads(count_thread) shared(img, width, height, radius, kernel)
    {
        for (int t = 0; t < static_cast<int>(array.size()); t++) {
            if (t % count_thread == omp_get_thread_num()) {
                int j_start = array[t][0];
                int j_finish = array[t][0] + block_height;
                int i_start = array[t][1];
                int i_finish = array[t][1] + block_width;
                for (int i = i_start; i < i_finish && i < width; i++) {
                    for (int j = j_start; j < j_finish && j < height; j++) {
                        int color = calculateNewPixelColor(img, width, height, i, j, radius, kernel);
                        resultImage[j * width + i] = color;
                    }
                }
            }
        }
    }
    return resultImage;
}
std::vector<float> createGaussianKernel(int radius, float sigma) {
    int size = 2 * radius + 1;
    std::vector<float> kernel(size * size);
    float norm = 0;
    for (int i = -radius; i <= radius; i++) {
        for (int j = -radius; j <= radius; j++) {
            kernel[(i + radius)* size + j + radius] = static_cast<float>(exp(-(i * i + j * j) / (2 * sigma * sigma)));
            norm = norm + kernel[(i + radius) * size + j + radius];
        }
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            kernel[i * size + j] = kernel[i * size + j] / norm;
        }
    }
    return kernel;
}

int calculateNewPixelColor(std::vector<int> img, int width, int height,
    int x, int y, int radius, std::vector<float> kernel) {
    int size = radius * 2 + 1;
    double sumColor = 0;
    for (int l = -radius; l <= radius; l++) {
        for (int k = -radius; k <= radius; k++) {
            int idX = Clamp(x + k, 0, width - 1);
            int idY = Clamp(y + l, 0, height - 1);
            int neighborColor = img[idY * width + idX];
            sumColor += neighborColor * kernel[(k + radius) * size + l + radius];
        }
    }
    return Clamp(static_cast<int>(sumColor), 0, 255);
}
int Clamp(int value, int min, int max) {
    if (value < min) {
        return min;
    }
    if (value > max) {
        return max;
    }
    return value;
}

