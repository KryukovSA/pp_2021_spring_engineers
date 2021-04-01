// Copyright 2020 Egorov Kirill
#include "../../../modules/task_1/egorov_k_gauss_filter_seq/egorov_k_gauss_filter_seq.h"

std::vector<int> getRandomVector(int sz) {
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    std::vector<int> vec(sz);
    for (int i = 0; i < sz; i++) { vec[i] = gen() % 100; }
    return vec;
}

int clamp(int value, int min, int max) {
    if (value < min)
        return min;
    else if (value > max)
        return max;
    else
        return value;
}

std::vector<float> calculateKernel3x3(float sigma) {
    std::vector<float> kernel(9);  // 3*3 kernel vector
    float n = 0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            kernel[(i + 1) * 3 + j + 1] = (exp(-(i * i + j * j)
                                          / (2 * sigma * sigma)));
            n = n + kernel[(i + 1) * 3 + j + 1];
        }
    }

    for (int i = 0; i < 9; i++) {
        kernel[i] = kernel[i] / n;
    }

    return kernel;
}

int pColourCalculation(const std::vector<int> &img, int w, int h,
                       int x, int y, std::vector<float> kernel) {
    int nColour = 0;
    float sColour = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            x = clamp(x + j, 0, w - 1);
            y = clamp(y + i, 0, h - 1);
            nColour = img[x * w + y];
            sColour += nColour * kernel[(j + 1) * 3 + i + 1];
        }
    }

    return clamp(static_cast<int>(sColour), 0, 255);
}

std::vector<int> filterApply(const std::vector<int> &img,
    int w, int h, float sigma) {
    std::vector<int> res(w * h);
    std::vector<float> kernel(9);

    kernel = calculateKernel3x3(sigma);

    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            res[i*w + j] = pColourCalculation(img, w, h, i, j, kernel);
        }
    }

    return res;
}
