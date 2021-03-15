// Copyright 2021 Khismatulina Karina
#include <vector>
#include <cassert>
#include <random>
#include "../../../modules/task_1/khismatulina_k_gradient/seq.h"

std::vector<int> getRandomVector(int size) {
	assert(size > 0);
	std::random_device rd;
	std::mt19937 mersenne(rd());
	std::vector<int> vec(size, 1);
	for (int i = 0; i < size; ++i) {
		vec[i] = mersenne() * mersenne() % 7;
	}
	return vec;
}

std::vector<int> getRandomMatrix(int size) {
	//size - размер стороны квадратной матрицы
	assert(size > 0);
	std::random_device rd;
	std::mt19937 mersenne(rd());
	std::vector<int> matrix(size, 1);
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			matrix[i * size + j] = matrix[j * size + i] = mersenne() * mersenne() % 7;
		}
	}
	return matrix;
}

 int vecMult(std::vector<int> A, std::vector<int> B) {
	assert(A.size() == B.size());
	int result = 0;
	for (int i = 0; i < A.size(); ++i) {
		result += A[i] * B[i];
	}
	return result;
}

std::vector<int> matrixVecMult(std::vector<int> m, std::vector<int> v) {
	assert(m.size() % v.size() == 0);
	std::vector<int> result(m.size() / v.size());
	for (int i = 0; i < result.size(); ++i) {
		result[i] = 0;
		for (int j = 0; j < v.size(); ++j) {
			result[i] += m[i * v.size() + j] * v[i];
		}
	}
	return result;
}

std::vector<int> gradientSeq(const std::vector<int>& matrix, const std::vector<int>& vector, int size) {

}
