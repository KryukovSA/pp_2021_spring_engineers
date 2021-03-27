// Copyright 2021 Elandaev Pavel

#include "../../modules/task_1/elandaev_p_integral_rectangle/rectangle.h"

double RectangleIntegral(double start, double end, std::function<double(double)> f, double step) {
    if (end < start)
        throw "wrong interval";
    if (step <= 0)
        throw "wrong splitting: smallest";
    if (step > end - start)
        throw "step is biggest";
    int countstep = static_cast<int>(end - start) / step;
    double x;
    double sum = 0.0;
    for (double i = 0.0; i < countstep; i ++) {
        x = start + i * step;
        sum += f(x);
    }
    return (step * sum);
}
