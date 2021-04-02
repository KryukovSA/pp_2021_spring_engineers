// Copyright 2021 Ptitsyn Pavel
#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include "../../../modules/task_1/ptitsyn_p_bbb_sort/bbb_sort.h"

template <class T>
void check_arrays(const std::vector<T>& lhs, const std::vector<T>& rhs) {
    ASSERT_EQ(lhs.size(), rhs.size());
    for (size_t i = 0; i < lhs.size(); ++i) {
        ASSERT_EQ(lhs[i], rhs[i]);
    }
}

TEST(RadixSortBatcherMerge, radix_empty) {
        std::vector<double> array(0u);
        std::vector<double> array_cpy(array);

        radix_sort(array.begin(), array.end());
        std::sort(array_cpy.begin(), array_cpy.end());

        check_arrays(array, array_cpy);
}

TEST(RadixSortBatcherMerge, radix_one_element) {
    std::vector<double> array = random_double_array(1u);
    std::vector<double> array_cpy(array);

    radix_sort(array.begin(), array.end());
    std::sort(array_cpy.begin(), array_cpy.end());

    check_arrays(array, array_cpy);
}

TEST(RadixSortBatcherMerge, radix_few_elements) {
    std::vector<double> array = random_double_array(10u);
    std::vector<double> array_cpy(array);

    radix_sort(array.begin(), array.end());
    std::sort(array_cpy.begin(), array_cpy.end());

    check_arrays(array, array_cpy);
}

TEST(RadixSortBatcherMerge, radix_lots_of_elements) {
    std::vector<double> array = random_double_array(1000u);
    std::vector<double> array_cpy(array);

    radix_sort(array.begin(), array.end());
    std::sort(array_cpy.begin(), array_cpy.end());

    check_arrays(array, array_cpy);
}

TEST(Radix_Sort_W_Batcher, Test_Batcher_3x3) {
    std::vector<double> part1 = {7, 2, 5.1 };
    std::vector<double> part2 = { 1, 9, 5.2 };
    std::sort(part1.begin(), part1.end());
    std::sort(part2.begin(), part2.end());
    std::vector<double> even = evenBatch(part1, part2);
    std::vector<double> odd = oddBatch(part1, part2);
    std::vector<double> res = EvenOddBatch(even, odd);
    std::vector<double>stl_mege(6);
    std::merge(part1.begin(), part1.end(), part2.begin(),
        part2.end(), stl_mege.begin());
    ASSERT_EQ(stl_mege, res);
}

TEST(Radix_Sort_W_Batcher, Test_Batcher) {
    std::vector<double> part1 = random_double_array(10u);
    std::vector<double> part2 = random_double_array(10u);
    std::sort(part1.begin(), part1.end());
    std::sort(part2.begin(), part2.end());
    std::vector<double> even = evenBatch(part1, part2);
    std::vector<double> odd = oddBatch(part1, part2);
    std::vector<double> res = EvenOddBatch(even, odd);
    std::vector<double>stl_mege(20);
    std::merge(part1.begin(), part1.end(), part2.begin(),
        part2.end(), stl_mege.begin());
    ASSERT_EQ(stl_mege, res);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
