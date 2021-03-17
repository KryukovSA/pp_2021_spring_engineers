// Copyright 2021 Oganyan Robert

#include "../../modules/task_1/oganyan_r_mark_components/mark_components.h"

static const std::vector<std::pair<int, int>> directions{
       // {-1, -1},
        {-1, 0},
      //  {-1, 1},
        {0,  -1},
        {0,  1},
       // {1,  -1},
        {1,  0},
       // {1,  1},
};

void bfs(std::vector<uint16_t>* img, std::pair<uint16_t, uint16_t> start,
                    uint16_t* number, uint16_t width, uint16_t height) {
    if ((*img)[start.first * width + start.second] != 1) {
        return;
    }
    std::queue<std::pair<uint16_t, uint16_t>> q;
    q.push({start});
    (*img)[start.first * width + start.second] = ++(*number);
    while (!q.empty()) {
        auto cur{q.front()};
        q.pop();
        for (auto &neighbor : directions) {
            if (cur.first + neighbor.first >= height || cur.first + neighbor.first < 0
                || cur.second + neighbor.second >= width || cur.second + neighbor.second < 0) {
                continue;
            }
            if ((*img)[(cur.first + neighbor.first) * width + cur.second + neighbor.second] == 1) {
                q.push({(cur.first + neighbor.first), cur.second + neighbor.second});
                (*img)[(cur.first + neighbor.first) * width + cur.second + neighbor.second] = (*number);
            }
        }
    }
    return;
}


std::pair<std::vector<uint16_t>, uint16_t> MarkComponents(std::vector<uint16_t> img, uint16_t height, uint16_t width) {
    if (img.size() == 0) {
        throw std::invalid_argument("Size of the image cant be negative");
    }
    if (img.size() != width * height) {
        throw std::invalid_argument("Size of the image is not correct");
    }
    uint16_t count_comp{1};
    for (uint16_t i{0}; i < height; ++i) {
        for (uint16_t j{0}; j < width; ++j) {
            bfs(&img, {i, j}, &count_comp, width, height);
        }
    }
    return {img, count_comp - 1};
}
