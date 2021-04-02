// Copyright 2021 Chesnokov Artyom

#ifndef MODULES_TASK_1_CHESNOKOV_A_JARVIS_JARVIS_H_
#define MODULES_TASK_1_CHESNOKOV_A_JARVIS_JARVIS_H_

#include <math.h>
#include <vector>
#include <iostream>
#include <list>

bool almost_equal(double x, double y, int ulp);

class Point {
 public:
  double x, y;

  Point(double x, double y)
    : x(x), y(y) {
  }

  Point(const Point& other) = default;

 public:
  bool operator==(const Point& other) const {
    return (almost_equal(x, other.x, 2) && almost_equal(y, other.y, 2));
  }

  bool operator!=(const Point& other) const {
    return !(*this == other);
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

  double length() {
    return sqrt(x * x + y * y);
  }

  double distance(const Point& other) const {
    Point v = other - *this;
    return v.length();
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
  static Point findWithMinAngle(const Point& prev, const Point& cur, std::list<Point>* in);

  static inline Point LAST(const std::vector<Point>& v) {
    return v.back();
  }

  static inline Point PRE_LAST(const std::vector<Point>& v) {
    return v[v.size() - 2];
  }
};

#endif  // MODULES_TASK_1_CHESNOKOV_A_JARVIS_JARVIS_H_
