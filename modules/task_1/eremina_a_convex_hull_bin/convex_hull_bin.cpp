// Copyright 2021 Eremina Alena
#include "../../../modules/task_1/eremina_a_convex_hull_bin/convex_hull_bin.h"
#include <math.h>
#include <map>
#include <vector>
#include <stack>
#include <random>
#include <ctime>
#define PI 3.1416

// Generate binary image
std::vector<int> generateImage(const int wigth, const int height) {
    std::vector<int> img_src_dst(wigth*height);
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < wigth * height; i++) {
        int r = gen() % 5;
        if (r == 0) {
            img_src_dst[i] = 1;
        } else {
            img_src_dst[i] = 1;
        }
    }
    return img_src_dst;
}

// Split binary image into components
std::map<int, int> splitImageIntoComponents(std::vector<int>* img_src_dst,
    const int width, const int height) {
    int kn = 0, km = 0;
    int count = 1;
    int A, B, C;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            kn = j - 1;
            if (kn < 0) {
                kn = 0;
                B = 0;
            } else {
                B = img_src_dst->data()[i * width + kn];
            }
            km = i - 1;
            if (km < 0) {
                km = 0;
                C = 0;
            } else {
                C = img_src_dst->data()[km * width + j];
            }
            A = img_src_dst->data()[i * width + j];
            if (A == 0) {
                continue;
            } else if (B == 0 && C ==0) {
                count++;
                img_src_dst->data()[i * width + j] = count;
            } else if (B != 0 && C == 0) {
                img_src_dst->data()[i * width + j] = B;
            } else if (B == 0 && C != 0) {
                img_src_dst->data()[i * width + j] = C;
            } else if (B != 0 && C != 0) {
                if (B == C) {
                    img_src_dst->data()[i * width + j] = B;
                } else {
                    img_src_dst->data()[i * width + j] = B;
                    for (int u = 0; u < height; u++) {
                        for (int v = 0; v < width; v++) {
                            if (img_src_dst->data()[u * width + v] == C) {
                                img_src_dst->data()[u * width + v] = B;
                            }
                        }
                    }
                }
            }
        }
    }

    std::map<int, int> marks;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (img_src_dst->data()[i * width + j] == 0) {
                continue;
            } else {
                auto f = marks.find(img_src_dst->data()[i * width + j]);
                if (f != marks.end()) {
                    int count = f->second + 1;
                    marks[img_src_dst->data()[i * width + j]] = count;
                } else {
                    marks[img_src_dst->data()[i * width + j]] = 1;
                }
            }
        }
    }

    return marks;
}

// Sort points in ascending order of polar angle,
// measured counterclockwise from point p0;
// If the polar angles of several points coincide,
// then the distance to the point p0
void sortPolar(point* points, const point p0, const int count) {
    for (int i = 0; i < count; i++) {
        int y = points[i].y - p0.y;
        int x = points[i].x - p0.x;
        double polar_angle = atan2(y, x);
        if (polar_angle < 0) polar_angle += 2*PI;
        points[i].polar_angle = polar_angle;
        points[i].distanse_p0 = sqrt(x * x + y * y);
    }

    point temp = {0, 0, 0, 0};
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (points[j].polar_angle > points[j + 1].polar_angle) {
                temp = points[j];
                points[j] = points[j + 1];
                points[j + 1] = temp;
            } else if (abs(points[j].polar_angle - points[j + 1].polar_angle)
                       < 0.000001) {
                if (points[j].distanse_p0 < points[j + 1].distanse_p0
                    && points[j].distanse_p0 != 0) {
                    temp = points[j];
                    points[j] = points[j + 1];
                    points[j + 1] = temp;
                }
            }
        }
    }
}

// Do the three points a, b and c make a right turn (with or without =)?
bool rightTurn(const point a, const point b, const point c, bool flag) {
    point u = {b.x - a.x, b.y - a.y, 0, 0};
    point v = {c.x - b.x, c.y - b.y, 0, 0};
    if (flag) {
        return u.x * v.y - u.y * v.x <= 0;
    }
    return u.x * v.y - u.y * v.x < 0;
}

// Graham's algorithm - an algorithm for constructing a convex hull
// in two-dimensional space
std::vector<int> Convex_Hull(std::vector<int> img_src,
    const int height, const int width) {
    // Output data
    std::vector<int> img_dst(height * width, 0);

    // Copy img_src to img_mark
    std::vector<int> img_mark(height * width);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            img_mark[i * width + j] = img_src[i * width + j];
        }
    }

    // Split binary image into components
    std::map<int, int> marks = splitImageIntoComponents(&img_mark,
        width, height);

    for (auto mark : marks) {
        if (mark.second <= 3) {
            int cnt = 0;
            for (int i = 0; i < height && cnt < mark.second; i++) {
                for (int j = 0; j < width && cnt < mark.second; j++) {
                    if (img_mark[i * width + j] == mark.first) {
                        img_dst[i * width + j] = 1;
                        cnt++;
                    }
                }
            }
            continue;
        }
        // p0 - point with the minimum Y or the leftmost one
        point p0 = {width, height, 0, 0};
        // points - array of all points of the component
        point* points = new point[mark.second];
        // count - number of founded points of the component
        int count = 0;

        // find p0
        for (int i = 0; i < height && count < mark.second; i++) {
            for (int j = 0; j < width && count < mark.second; j++) {
                if (img_mark[i * width + j] == mark.first) {
                    points[count] = {j, i, 0, 0};
                    count++;
                    if (i < p0.y) {
                        p0.x = j;
                        p0.y = i;
                    }
                    if (i == p0.y) {
                        if (j < p0.x) {
                            p0.x = j;
                            p0.y = i;
                        }
                    }
                }
            }
        }

        // Sort points
        sortPolar(points, p0, count);

        std::stack<point> S;
        S.push(p0);
        S.push(points[1]);
        for (int i = 2; i < count; i++) {
            point top = S.top();
            S.pop();
            point next_to_top = S.top();
            S.push(top);
            while (rightTurn(next_to_top, top, points[i], 0)) {
                S.pop();
                top = S.top();
                S.pop();
                next_to_top = S.top();
                S.push(top);
            }
            S.push(points[i]);
        }

        point elem = {-1, -1, 0, 0};
        point begin = S.top();
        point b = begin;
        img_dst[begin.y * width + begin.x] = 1;
        S.pop();
        bool flag = true;
        while (flag) {
            if (!S.empty()) {
                elem = S.top();
                S.pop();
            } else {
                elem = b;
                flag = false;
            }
            while (abs(begin.x - elem.x) > 1 || abs(begin.y - elem.y) > 1) {
                int step_x, step_y;
                if (begin.x > elem.x) {
                    step_x = -1;
                } else if (begin.x < elem.x) {
                    step_x = 1;
                } else {
                    step_x = 0;
                }
                if (begin.y > elem.y) {
                    step_y = -1;
                } else if (begin.y < elem.y) {
                    step_y = 1;
                } else {
                    step_y = 0;
                }

                std::stack<point> new_points;
                point tmp[3] = {{begin.x + step_x, begin.y + step_y, 0, 0},
                                {begin.x, begin.y + step_y, 0, 0},
                                {begin.x + step_x, begin.y, 0, 0}};
                double min_dist = height + width;
                int min_tmp = 0;
                for (int i = 0; i < 3; i++) {
                    if (rightTurn(begin, tmp[i], elem, 1)) {
                        tmp[i].distanse_p0 =
                            sqrt((begin.x - tmp[i].x) * (begin.x - tmp[i].x) +
                                 (begin.y - tmp[i].y) * (begin.y - tmp[i].y)) +
                            sqrt((elem.x - tmp[i].x) * (elem.x - tmp[i].x) +
                                 (elem.y - tmp[i].y) * (elem.y - tmp[i].y));
                        if (tmp[i].distanse_p0 < min_dist) {
                            min_dist = tmp[i].distanse_p0;
                            min_tmp = i;
                        }
                    }
                }
                img_dst[tmp[min_tmp].y * width + tmp[min_tmp].x] = 1;
                begin = tmp[min_tmp];
            }
            img_dst[elem.y * width + elem.x] = 1;
            begin = elem;
        }

        delete [] points;
    }
    return img_dst;
}
