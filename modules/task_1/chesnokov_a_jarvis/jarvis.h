// Copyright 2021 Chesnokov Artyom

#include <vector>
#include <iostream>
#include <math.h>
#include <list>

class Point {
public:
  
  double x, y;
  
  Point(double x = 0.0, double y = 0.0)
    : x(x), y(y) {
  }
  
  Point(const Point& other) = default;
  
  bool operator==(const Point& other) const {
    return (x == other.x && y == other.y);
  }
  
  bool operator!=(const Point& other) const {
    return !(*this==other);
  }
  
  Point operator-(const Point& other) const {
    return Point(x - other.x, y - other.y);
  }
  
  Point operator+(const Point& other) const {
    return Point(x + other.x, y + other.y);
  }
  
  friend std::ostream& operator<< (std::ostream& out, const Point& p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;
  }
  
  double cosine(const Point& other) const {
    double len1 = sqrt(x * x + y * y);
    double len2 = sqrt(other.x * other.x + other.y * other.y);
    double dot = x * other.x + y * other.y;
    return dot / (len1 * len2);
  }
  
  double distance(const Point& other) const {
    Point v = other - *this;
    return sqrt(v.x * v.x + v.y * v.y);
  }
};

class Jarvis {
public:

  // Computes the convex hull of a given set of points (in).
  // degenerate case 1: from set of identical points, only one arbitrary is taken;
  // degenerate case 2: from colinear vertices of CH only extreme pts are taken;
  // degenerate case 3: CH of set of 1 or 2 pts is this set itself;
  static std::vector<Point> makeHull(std::list<Point> in);

private:

  // Finds the leftmost point; if there are several, returns lowest one.
  static Point findLeftmost(const std::list<Point>& in);
  
  // Finds from list in the point P, such that angle between vec(prev, cur) and vec(cur, P) is minimal.
  // If there are several, then it chooses the most distant one.
  // The found point will be deleted from the list.
  static Point findWithMinAngle(const Point& prev, const Point& cur, std::list<Point>& in);
  
  static inline Point LAST(const std::vector<Point>& v) {
    return v.back();
  }
  
  static inline Point PRE_LAST(const std::vector<Point>& v) {
    return v[v.size() - 2];
  }
};
