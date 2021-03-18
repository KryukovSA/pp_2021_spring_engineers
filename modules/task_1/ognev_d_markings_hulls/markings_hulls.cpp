// Copyright 2021 Ognev Denis

#include <../../modules/task_1/ognev_d_markings_hulls/markings_hulls.h>

#include <algorithm>
#include <iostream>
#include <list>
#include <set>
#include <vector>
#include <random>

std::vector<int> tree(1, 0);
int border = 135;

std::vector<bool> GenerateRandomMap(int width, int height) {
  if (width < 1 || height < 1) throw;
  std::mt19937 random;
  std::uniform_real_distribution<> urd(0, 1);
  random.seed(static_cast<unsigned int>(time(0)));
  std::vector<bool> result(width * height);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      float r = urd(random);
      if (r > 0.7f)
        result[i * width + j] = false;
      else
        result[i * width + j] = true;
    }
  }
  return result;
}

std::vector<bool> GenerateConnectedMap(int width, int height) {
  if (width < 1 || height < 1) throw;
  std::mt19937 random;
  std::uniform_real_distribution<> urd(0, 1);
  random.seed(static_cast<unsigned int>(time(0)));
  std::vector<bool> result(width * height);
  int index;
  float r1 = urd(random);
  if (r1 > 0.5f)
    result[0] = true;
  else
    result[0] = false;
  for (int i = 1; i < width * height; i++) {
    float r = urd(random);
    if (i > width) {
      if (i % width != 0) {
        index = i - width;
        if (result[index] == true) {
          index = i - 1;
          if (result[index] == true) {
            if (r > 0.2f) {
              result[i] = true;
            } else {
              result[i] = false;
            }
          } else {
            if (r > 0.4f) {
              result[i] = true;
            } else {
              result[i] = false;
            }
          }
        } else {
          index = i - 1;
          if (result[index] == true) {
            if (r > 0.4f) {
              result[i] = false;
            } else {
              result[i] = true;
            }
          } else {
            if (r > 0.2f) {
              result[i] = false;
            } else {
              result[i] = true;
            }
          }
        }
      }
    } else {
      index = i - 1;
      if (result[index] == true) {
        if (r > 0.2f) {
          result[i] = true;
        } else {
          result[i] = false;
        }
      } else {
        if (r > 0.2f) {
          result[i] = false;
        } else {
          result[i] = true;
        }
      }
      continue;
    }
    if (i % width == 0) {
      index = i - width;
      if (result[index] == true) {
        if (r > 0.2f) {
          result[i] = true;
        } else {
          result[i] = false;
        }
      } else {
        if (r > 0.2f) {
          result[i] = false;
        } else {
          result[i] = true;
        }
      }
    }
  }

  return result;
}

int findInTree(int x) {
  while (tree[x] != 0) x = tree[x];
  return x;
}

void unionInTree(int x, int y) {
  x = findInTree(x);
  y = findInTree(y);
  if (y != x) tree[y] = x;
}

std::vector<int> firstStep(std::vector<bool> map, int width, int height) {
  if (width < 1 || height < 1 || map.empty()) {
    throw "";
  }
  // use tree table for solving border problem
  std::vector<int> result(width * height);
  int label = 0;

  for (int i = 0; i < width * height; i++) {
    result[i] = 0;
    if (map[i] != false) {
      if (label == 0) {  // set first label (solves 0, 0)
        tree.push_back(0);
        label++;
        result[i] = label;
      } else if (i < width) {  // first row
        if (result[i - 1] != 0) {
          result[i] = result[i - 1];
        } else {
          tree.push_back(0);
          label++;
          result[i] = label;
        }
      } else if (i % width == 0) {  // first column
        if (result[i - width] != 0) {
          result[i] = result[i - width];
        } else {
          tree.push_back(0);
          label++;
          result[i] = label;
        }
      } else {
        if (result[i - width] != 0) {
          if (result[i - 1] != 0) {
            if (result[i - width] != result[i - 1]) {
              int first = result[i - width];
              int second = result[i - 1];
              unionInTree(first, second);
            }
          }
          result[i] = result[i - width];
        } else if (result[i - 1] != 0) {
          result[i] = result[i - 1];
        } else {
          tree.push_back(0);
          label++;
          result[i] = label;
        }
      }
    }
  }
  return result;
}

std::vector<int> secondStep(std::vector<int> map, int width, int height) {
  if (width < 1 || height < 1 || map.empty()) throw "";
  if (tree.size() == 1)
    // if no elements were added to tree table -> no collisions
    return map;
  std::vector<int> result(map);
  for (int i = 0; i < width * height; i++) {
    if (result[i] != 0) {
      result[i] = findInTree(result[i]);  // searching parent
    }
  }
  return result;
}

int orientTriangle2(int x1, int y1, int x2, int y2, int x3, int y3) {
  return (x2 - x1) * (y3 - y2) - (y2 - y1) * (x3 - x2);
}

bool isInside(int x1, int y1, int x2, int y2, int x3, int y3) {
  if ((x2 >= x1 && x2 <= x3 && y2 >= y1 && y2 <= y3) ||
      (x2 >= x3 && x2 <= x1 && y2 >= y1 && y2 <= y3) ||
      (x2 >= x1 && x2 <= x3 && y2 >= y3 && y2 <= y1) ||
      (x2 >= x3 && x2 <= x1 && y2 >= y3 && y2 <= y1)) {
    return true;
  }
  return false;
}

std::vector<int> jarvis(std::vector<int> map, int width, int height, int mark,
                        int index) {
  if (width < 1 || height < 1 || index < 0 || mark < 0 || map.empty()) throw "";
  std::vector<int> temp(map);
  int first = index;
  int current = index;

  if (map[index] == mark) map[index] = border;

  do {
    bool marked = false;
    int next = current;
    for (int i = 0; i < width * height; i++) {
      if (temp[i] == mark) {
        int sign =
            orientTriangle2(current / width, current % width, next / width,
                            next % width, i / width, i % width);
        if (sign > 0) {
          marked = true;
          next = i;
        } else if (sign == 0) {
          if (isInside(current / width, current % width, next / width,
                       next % width, i / width, i % width)) {
            marked = true;
            next = i;
          }
        }
      }
    }
    if (marked && next != first) {
      marked = false;
      map[next] = border;
    }
    current = next;
  } while (current != first);

  border++;
  return map;
}

std::vector<int> convexHull(std::vector<int> map, int width, int height) {
  if (width < 1 || height < 1 || map.empty()) throw "";
  std::vector<int> result(map);
  std::set<int> marks(map.begin(), map.end());
  marks.erase(0);

  for (int j = 0; j < width; j++) {
    for (int i = 0; i < height; i++) {
      if (result[i * width + j] != 0) {
        if (marks.find(result[i * width + j]) != marks.end()) {
          marks.erase(result[i * width + j]);
          result = jarvis(result, width, height, result[i * width + j],
                          i * width + j);
        }
      }
    }
  }

  return result;
}
