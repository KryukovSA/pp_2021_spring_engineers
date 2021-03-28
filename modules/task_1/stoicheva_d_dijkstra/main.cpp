// Copyright 2021 Stoicheva Darya
#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include "../../../modules/task_1/stoicheva_d_dijkstra/dijkstra.h"

TEST(Sequential, Test_EmptyGraph) {
    std::vector<int> graph = {};

    ASSERT_ANY_THROW(dijkstra(graph, 0));
}

TEST(Sequential, Test_Graph1) {
    std::vector<int> graph = {0};
    std::vector<int> result = {0};

    ASSERT_EQ(result, dijkstra(graph, 0));
}

TEST(Sequential, Test_Graph2) {
    std::vector<int> graph = { 0, 7,
                               7, 0 };
    std::vector<int> result = {0, 7};

    ASSERT_EQ(result, dijkstra(graph, 0));
}

TEST(Sequential, Test_Graph6) {
    std::vector<int> graph = { 0, 7, 9, -1, -1, 14,
                              7, 0, 10, 15, -1, -1,
                              9, 10, 0, 11, -1, 2,
                              -1, 15, 11, 0, 6, -1,
                              -1, -1, -1, 6, 0, 9,
                               14, -1, 2, -1, 9, 0 };
    std::vector<int> result = { 0, 7, 9, 20, 20, 11 };

    ASSERT_EQ(result, dijkstra(graph, 0));
}

TEST(Sequential, Test_Graph6a) {
    std::vector<int> graph = { 0, 1, 4, -1, 2, -1,
                              1, 0, -1, 9, -1, -1,
                              4, -1, 0, 7, -1, -1,
                              -1, 9, 7, 0, -1, 2,
                              2, -1, -1, -1, 0, 8,
                              -1, -1, -1, 2, -1, 0 };
    std::vector<int> result = { 0, 1, 4, 10, 2, 10 };

    ASSERT_EQ(result, dijkstra(graph, 0));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
