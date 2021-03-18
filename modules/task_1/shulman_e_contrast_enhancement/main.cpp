// Copyright 2021 Shulman Egor
#include <gtest/gtest.h>
#include "./contrast_enhancement.h"

TEST(Sequential, testCreateMatrix) {
    int n = 100, m = 100;
    ASSERT_NO_THROW(getRandomMatrix(n, m));
}

TEST(Sequential, testRowsNegative) {
    int n = -100, m = 100;
    ASSERT_ANY_THROW(getRandomMatrix(n, m));
}

TEST(Sequential, testColumnsNegative) {
    int n = 100, m = -100;
    ASSERT_ANY_THROW(getRandomMatrix(n, m));
}

TEST(Sequential, testRowsAndColumnsNegative) {
    int n = -100, m = -100;
    ASSERT_ANY_THROW(getRandomMatrix(n, m));
}

TEST(Sequential, testContrastEnhancement) {
    int n = 100, m = 100;
    std::vector<int> matrix = getRandomMatrix(n, m);
    ASSERT_NO_THROW(ContrastEnhancement(matrix));
}

TEST(Sequential, testComparisonWithExpected) {
    int n = 3, m = 3;

    std::vector<int> matrix(n * m);
    std::vector<int> result(n * m);
    for (int i = 0; i < n * m; ++i) {
        matrix[i] = i + 10;
        result[i] = i + 10;
    }

    matrix = ContrastEnhancement(matrix);

    int yMax = *std::max_element(result.begin(), result.end());
    int yMin = *std::min_element(result.begin(), result.end());
    for (size_t i = 0; i < result.size(); ++i)
        result[i] = (result[i] - yMin) * (255 / (yMax - yMin));

    ASSERT_EQ(result, matrix);;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
