// Copyright 2021 Gavrilov Nikita
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <ctime>
#include <random>
// #include <chrono>
#include "../../modules/task_1/gavrilov_n_batcher_merging_sort/BatcherMergingSort.h"

bool IsSorted(const std::vector<int>& data) {
    if (data.size() == 0)
        return true;
    for (size_t i = 0; i < data.size() - 1; i++) {
        if (data[i] > data[i + 1])
            return false;
    }
    return true;
}
std::vector<int> GetRandomVector(size_t size) {
    std::mt19937 rnd;
    rnd.seed(static_cast<unsigned int>(time(0)));

    std::vector<int> result(size);
    for (size_t i = 0; i < size; i++) {
        result[i] = rnd() % 20000 - 10000;
    }

    return result;
}

TEST(Parallel_Operations_MPI, No_Throw_SplitCount1to10) {
    for (int i = 1; i <= 10; i++) {
        std::vector<int> data = GetRandomVector(10000);
        ASSERT_NO_THROW(Sort(&data, i));
    }
}

TEST(Parallel_Operations_MPI, Sorting_Right_SplitCount1to10) {
    for (int i = 1; i <= 10; i++) {
        std::vector<int> data = GetRandomVector(10000);
        Sort(&data, i);
        ASSERT_TRUE(IsSorted(data));
    }
}

TEST(Parallel_Operations_MPI, Sorting_Time_SplitCount1to10) {
    int count = 10000;
    for (int i = 1; i <= 10; i++) {
        std::vector<int> data = GetRandomVector(count);

        // auto begin = std::chrono::high_resolution_clock::now();
        Sort(&data, i);
        // auto end = std::chrono::high_resolution_clock::now();

        // auto t = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        // std::cout << "time of (splitCount=" << i << " count = " << count << ") : " << t << std::endl;
        std::cout << "can't use chrono lib" << std::endl;
    }
}

TEST(Parallel_Operations_MPI, Sort_By_Num_Place_Rang10) {
    std::vector<int> data = GetRandomVector(10000);
    ASSERT_NO_THROW(SortByNumPlace(&data, 10));
    ASSERT_TRUE(IsSorted(data));
}

TEST(Parallel_Operations_MPI, Sort_By_Num_Place_Rang2) {
    std::vector<int> data = GetRandomVector(10000);
    ASSERT_NO_THROW(SortByNumPlace(&data, 2));
    ASSERT_TRUE(IsSorted(data));
}

TEST(Parallel_Operations_MPI, Sorting_Right_Even_If_Bad_Size_SplitCount1to10) {
    for (int j = 1; j <= 10; j++) {
        for (int i = 1; i < j; i++) {
            std::vector<int> data = GetRandomVector(j * 1000 + j - i);
            ASSERT_NO_THROW(Sort(&data, j));
            ASSERT_TRUE(IsSorted(data));
        }
    }
}

TEST(Parallel_Operations_MPI, Sorting_Right_Even_If_Bad_Size2_SplitCount1to10) {
    for (int j = 1; j <= 10; j++) {
        for (int i = 1; i <= j; i++) {
            std::vector<int> data = GetRandomVector(j - 1);
            ASSERT_NO_THROW(Sort(&data, j));
            ASSERT_TRUE(IsSorted(data));
        }
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
