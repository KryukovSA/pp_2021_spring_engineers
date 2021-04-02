// Copyright 2021 Zhafyarov Oleg
#ifndef MODULES_TASK_1_ZHAFYAROV_O_GRAHAM_PASS_GRAHAM_PASS_H_
#define MODULES_TASK_1_ZHAFYAROV_O_GRAHAM_PASS_GRAHAM_PASS_H_

#include <vector>

struct point {
  int x;
  int y;
};

std::vector<point> RandomVector(int size);
double Rotation(point a, point b, point c);
std::vector<size_t> GrahamPass(const std::vector<point>& basisVec, int* count);


#endif  // MODULES_TASK_1_ZHAFYAROV_O_GRAHAM_PASS_GRAHAM_PASS_H_
