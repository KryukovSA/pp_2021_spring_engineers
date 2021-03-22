#include "jarvis.h"

std::vector<Point> Jarvis::makeHull(std::list<Point> in)
{
    if (in.empty()) {
        // empty hull for empty list
        return std::vector<Point>();
    }

    // resulting convex hull
    std::vector<Point> hull;

    // for one point P the CH is the P
    if (in.size() == 1) {
        hull.emplace_back(in.front());
        return hull;
    }

    // 1) find the leftmost Point p0, it will be first CH's vertex
    hull.emplace_back(findLeftmost(in));

    // 2) find the second vertex of CH, assuming that first one is the leftmost
    // imag - is imaginary previous vertex, that is the same as p0 but shifted down
    Point imag = LAST(hull);
    imag.y -= 30.0;
    hull.emplace_back(findWithMinAngle(imag, LAST(hull), in));

    // 3) find next point of hull while last found != p0
    while (LAST(hull) != hull[0])
    {
        hull.emplace_back(findWithMinAngle(PRE_LAST(hull), LAST(hull), in));
    }

    hull.pop_back();

    return hull;
}

Point Jarvis::findLeftmost(const std::list<Point>& in)
{
    // leftmost
    auto lm = in.begin();

    for (auto it = in.begin(); it != in.end(); it++) {
        if (it->x < lm->x) {
            lm = it;
        }
        else if (it->x == lm->x && it->y < lm->y) {
            lm = it;
        }
    }

    // it's save to return list's iterator (no invalidation)
    return *lm;
}

Point Jarvis::findWithMinAngle(const Point& prev, const Point& cur, std::list<Point>& in)
{
    Point vec1 = cur - prev;
    // Stores the required point
    std::list<Point>::const_iterator minPt = in.begin();
    // The smaller angle between two vectors the bigger cos
    double maxCos = -2.0;
    for (auto it = in.begin(); it != in.end(); it++) {
        Point vec2 = *it - cur;
        double curCos = vec1.cosine(vec2);

        if (*it == cur) continue;

        if (curCos > maxCos) {
            maxCos = curCos;
            minPt = it;
        }

        else if (curCos == maxCos && cur.distance(*minPt) < cur.distance(*it)) {
            maxCos = curCos;
            minPt = it;
        }
    }

    Point res = *minPt;
    in.erase(minPt);
    return res;
}
