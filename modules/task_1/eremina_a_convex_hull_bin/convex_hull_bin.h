// Copyright 2021 Eremina Alena
#ifndef MODULES_TASK_1_EREMINA_A_CONVEX_HULL_BIN_CONVEX_HULL_BIN_H_
#define MODULES_TASK_1_EREMINA_A_CONVEX_HULL_BIN_CONVEX_HULL_BIN_H_

#include <vector>
#include <map>
#include <stack>

typedef struct {
    int x;
    int y;
    double polar_angle;
    double distanse_p0;
} point;

// Generate binary image
std::vector<int> generateImage(const int wigth, const int height);

// Split binary image into components
std::map<int, int> splitImageIntoComponents(
    std::vector<int>* img_src_dst, const int width, const int height);

// Sort points in ascending order of polar angle,
// measured counterclockwise from point p0;
// If the polar angles of several points coincide,
// then the distance to the point p0
void sortPolar(point* points, const point* p0, const int count);

// Do the three points a, b and c make a right turn (with or without =)?
bool rightTurn(const point* a, const point* b, const point* c, bool flag);

// Graham's algorithm - an algorithm for constructing
// a convex hull in two-dimensional space
std::vector<int> Convex_Hull(std::vector<int> img_src,
    const int height, const int width);

#endif  // MODULES_TASK_1_EREMINA_A_CONVEX_HULL_BIN_CONVEX_HULL_BIN_H_
