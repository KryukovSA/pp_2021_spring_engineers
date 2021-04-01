// Copyright 2020 Egorov Kirill
#ifndef MODULES_TASK_1_EGOROV_K_GAUSS_FILTER_SEQ_EGOROV_K_GAUSS_FILTER_SEQ_H_
#define MODULES_TASK_1_EGOROV_K_GAUSS_FILTER_SEQ_EGOROV_K_GAUSS_FILTER_SEQ_H_

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>

std::vector<int> getRandomVector(int  sz);
int clamp(int value, int min, int max);

std::vector<float> calculateKernel3x3(float sigma);
int pColourCalculation(const std::vector<int> &img, int w, int h,
    int x, int y, std::vector<float> kernel);
std::vector<int> filterApply(const std::vector<int> &img,
    int w, int h, float sigma);

#endif  // MODULES_TASK_1_EGOROV_K_GAUSS_FILTER_SEQ_EGOROV_K_GAUSS_FILTER_SEQ_H_
