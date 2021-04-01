// Copyright 2021 Kokh Vladislav
#include <gtest/gtest.h>
#include "./hoar_sort_batcher.h"

TEST(hoar_sort_batcher, simple_check_5000) {
    int size = 5000;
    double* mas = randomFunc(size);
    sortFunc(0, size - 1, mas);
    ASSERT_EQ(true, check(mas, size));
    delete[] mas;
}
TEST(hoar_sort_batcher, check_otr) {
    int size = 10000;
    double* mas = randomFunc(size);
    mas[7] = -100;
    sortFunc(0, size - 1, mas);
    ASSERT_EQ(true, check(mas, size));
    delete[] mas;
}
TEST(hoar_sort_batcher, simple_check_10000) {
    int size = 10000;
    double* mas = randomFunc(size);
    sortFunc(0, size - 1, mas);
    ASSERT_EQ(true, check(mas, size));
    delete[] mas;
}
TEST(hoar_sort_batcher, check_all_otr) {
    int size = 5000;
    double* mas = new double[size];
    for (int i = 0; i < size; ++i) {
        mas[i] = -i;
    }
    sortFunc(0, size - 1, mas);
    ASSERT_EQ(true, check(mas, size));
    delete[] mas;
}
TEST(hoar_sort_batcher, simple_check_all_zero) {
    int size = 5000;
    double* mas = new double[size];
    for (int i = 0; i < size; ++i) {
        mas[i] = -i;
    }
    mas[9] = 1;
    sortFunc(0, size - 1, mas);
    ASSERT_EQ(true, check(mas, size));
    delete[] mas;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
