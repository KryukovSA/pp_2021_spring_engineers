// Copyright 2021 Ognev Denis
#ifndef MODULES_TASK_1_OGNEV_D_MARKINGS_HULLS_MARKINGS_HULLS_H_
#define MODULES_TASK_1_OGNEV_D_MARKINGS_HULLS_MARKINGS_HULLS_H_

#include <vector>

std::vector<bool> GenerateRandomMap(int width, int height);
std::vector<bool> GenerateConnectedMap(int width, int height);
int findInTree(int x);
void unionInTree(int x, int y);
std::vector<int> firstStep(std::vector<bool> map, int width, int height);
std::vector<int> secondStep(std::vector<int> map, int width, int height);
int orientTriangle2(int x1, int y1, int x2, int y2, int x3, int y3);
bool isInside(int x1, int y1, int x2, int y2, int x3, int y3);
std::vector<int> jarvis(std::vector<int> map, int width, int height, int mark,
                        int index);
std::vector<int> convexHull(std::vector<int> map, int width, int height);

#endif  // MODULES_TASK_1_OGNEV_D_MARKINGS_HULLS_MARKINGS_HULLS_H_
