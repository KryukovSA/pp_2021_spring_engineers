// Copyright 2021 Kryukov Sergey
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "./kryukov_s_sparse_compl_mat.h"
// тесты будут с инициализированными структурами

TEST(seq_version, correct_create_sparse_mat) {
	int size = 3;
	std::vector<std::complex<double>> standartMat = {
		{0, 0}, {0, 2}, {0, 0},
		{0, 1}, {0, 0}, {0, 0},
		{0, 0}, {0, 1}, {0, 0},
	};
	crs_mat sparseMat;
	createSparseMat(size, standartMat, sparseMat);
	std::vector<std::complex<double>> rightVal = { {0, 2}, {0, 1}, {0, 1} };
	std::vector<int> rightCol = { 1, 0, 1 };
	std::vector<int> rightRowNum = { 0, 1, 2, 3 };
	ASSERT_EQ(sparseMat.size, size);
	ASSERT_EQ(sparseMat.val, rightVal);
	ASSERT_EQ(sparseMat.colNum, rightCol);
	ASSERT_EQ(sparseMat.rowNum, rightRowNum);
}

TEST(seq_version, correct_transpose_mat) {
	
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}