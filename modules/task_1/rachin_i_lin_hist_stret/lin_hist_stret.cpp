// Copyright 2021 Rachin Igor
#include "../../modules/task_1/rachin_i_lin_hist_stret/lin_hist_stret.h"
#include <random>
#include <vector>
#include <ctime>
std::vector<int> getRandomMatrix(int rows, int clmns) {
    if (rows <= 0 || clmns <= 0) {
        return std::vector<int>();
    }
    int sizeM = rows * clmns;
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    std::vector<int> mx(sizeM);
    for (int i = 0; i < sizeM; i++) {
            mx[i] = gen() % 256;
    }
    return mx;
}

std::vector<int> histogramStretching(const std::vector<int>& mx, int rows, int clmns) {
    std::vector<int> empty;
    if (rows <= 0 || clmns <= 0 || mx == empty) {
        return std::vector<int>();
    }
    int sizeM = rows * clmns;
    int maxIntensity = mx[0];
    int minIntensity = mx[0];
    std::vector<int> stretchedMatrix(sizeM);
    for (int i = 1; i < sizeM; i++) {
        if (mx[i] > maxIntensity) {
            maxIntensity = mx[i];
            continue;
        }
        if (mx[i] < minIntensity) {
            minIntensity = mx[i];
        }
    }
    for (int i = 0; i < sizeM; i++) {  // Formul of linear histogram stretching
        stretchedMatrix[i] = (mx[i] - minIntensity) * (255 / (maxIntensity - minIntensity));
    }
    return stretchedMatrix;
}
