#include <vector>
#include <list>

class Point {
public:

    double x, y;

    Point(double _x = 0.0, double _y = 0.0)
        : x(_x), y(_y) {

    }

    Point(const Point& other)
        : x(other.x), y(other.y) {

    }
};

class Jarvis {
public:

    static std::vector<Point> MakeHull(std::list<Point> in);

private:

    static Point& FindLeftmost(const std::list<Point>& in);
};