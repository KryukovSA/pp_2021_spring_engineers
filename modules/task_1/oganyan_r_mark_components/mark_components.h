// Copyright 2021 Oganyan Robert


#ifndef MODULES_TASK_1_OGANYAN_R_MARK_COMPONENTS_MARK_COMPONENTS_H_
#define MODULES_TASK_1_OGANYAN_R_MARK_COMPONENTS_MARK_COMPONENTS_H_

#include <vector>
#include <cstdint>
#include <queue>
#include <stdexcept>
#include <utility>


std::pair<std::vector<uint16_t>, uint16_t> MarkComponents(std::vector<uint16_t> img,
                                                          uint16_t height, uint16_t width);
void bfs(std::vector<uint16_t>* img, std::pair<uint16_t, uint16_t> start,
                uint16_t* number, uint16_t width, uint16_t height);

#endif  //  MODULES_TASK_1_OGANYAN_R_MARK_COMPONENTS_MARK_COMPONENTS_H_
