#include "jarvis.h"

std::vector<Point> Jarvis::MakeHull(std::list<Point> in)
{
    std::vector<Point> hull;
    // 1) find the leftmost Point p0
    hull.emplace_back(FindLeftmost(in));

    return hull;
}

Point& Jarvis::FindLeftmost(const std::list<Point>& in)
{
    return Point();
}
