// Copyright 2021 Elandaev Pavel
#ifndef MODULES_TASK_1_ELANDAEV_P_INTEGRAL_RECTANGLE_RECTANGLE_H_
#define MODULES_TASK_1_ELANDAEV_P_INTEGRAL_RECTANGLE_RECTANGLE_H_

#include <utility>
#include <vector>
#include <functional>

double RectangleIntegral(double start, double end, std::function<double(double)> f, double countstep);
#endif  // MODULES_TASK_1_ELANDAEV_P_INTEGRAL_RECTANGLE_RECTANGLE_H_
