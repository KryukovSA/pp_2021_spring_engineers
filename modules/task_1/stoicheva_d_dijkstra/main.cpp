// Copyright 2018 Nesterov Alexander
#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include "../../../modules/task_1/stoicheva_d_dijkstra/dijkstra.h"

TEST(DISABLED_Sequential, Test_Sum_10) {
    const int count = 10;
    int sum = 0;
    for (size_t i = 0; i < count; i++) {
        sum++;
    }
    ASSERT_EQ(count, sum);
}

TEST(DISABLED_Sequential, Test_Sum_20) {
    const int count = 20;
    int sum = 0;
    for (size_t i = 0; i < count; i++) {
        sum++;
    }
    ASSERT_EQ(count, sum);
}

TEST(DISABLED_Sequential, Test_Sum_50) {
    const int count = 20;
    int sum = 0;
    for (size_t i = 0; i < count; i++) {
        sum++;
    }
    ASSERT_EQ(count, sum);
}

TEST(DISABLED_Sequential, Test_Sum_70) {
    const int count = 20;
    int sum = 0;
    for (size_t i = 0; i < count; i++) {
        sum++;
    }
    ASSERT_EQ(count, sum);
}

TEST(DISABLED_Sequential, Test_Sum_100) {
    const int count = 100;
    int sum = 0;
    for (size_t i = 0; i < count; i++) {
        sum++;
    }
    ASSERT_EQ(count, sum);
}

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

TEST(Sequential, Test_Graph5) {
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
