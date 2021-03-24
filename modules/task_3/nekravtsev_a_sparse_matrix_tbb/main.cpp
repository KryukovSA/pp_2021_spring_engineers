// Copyright 2021 Nekravtsev Alexey
#include <gtest/gtest.h>
#include <tbb/tbb.h>
#include <cmath>
#include <ctime>
#include <vector>
#include "./sparse_matrix.h"

TEST(Seq, test_ordinary_mult) {
  std::vector<double> A = {
    0, 7, 3,
    10, 0, 5,
    19, 0, 2
  };
  std::vector<double> B = {
    1, 0, 3,
    0, 0, 5,
    9, 0, 0
  };
  std::vector<double> C = MultMatrix(3, A, B);

  std::vector<double> res = { 27, 0, 35, 55, 0, 30, 37, 0, 57 };
  bool check = true;
  for (size_t i = 0; i < res.size(); i++) {
    if (fabs(C[i] - res[i]) >= std::numeric_limits<double>::epsilon()) {
      check = false;
      break;
    }
  }

  ASSERT_EQ(true, check);
}

TEST(Seq, check_results_3x3) {
  CCS A = createCCS(3, std::vector<double> {
    25, 0, 38,
    0, 4, 43,
    9, 0, 0
  });
  CCS B = createCCS(3, std::vector<double> {
    1, 0, 3,
    0, 2, 5,
    9, 0, 0
  });
  CCS C = MultCCS(TranspSpareMatrix(A), B);

  std::vector<double> res = { 367, 387, 9, 8, 75, 20, 27 };
  bool check = true;
  for (size_t i = 0; i < res.size(); i++) {
    if (fabs(C.value[i] - res[i]) >= std::numeric_limits<double>::epsilon()) {
      check = false;
      break;
    }
  }

  ASSERT_EQ(true, check);
}

TEST(Seq, mult_zero_matr) {
  CCS A = createCCS(3, std::vector<double>(9, 0));
  CCS B = createCCS(3, std::vector<double> {
    1, 0, 3,
    0, 0, 5,
    9, 0, 0
  });
  CCS C = MultCCS(TranspSpareMatrix(A), B);
  ASSERT_EQ(true, C.value.empty());
}

TEST(Seq, mult_random_matr_3x3) {
  int size = 3;
  std::vector<double> a = GenSpareMatrix(size);
  std::vector<double> b = GenSpareMatrix(size);
  CCS c = createCCS(size, MultMatrix(size, a, b));

  CCS A = createCCS(size, a);
  CCS B = createCCS(size, b);
  CCS C = MultCCS(TranspSpareMatrix(A), B);

  bool check = true;
  for (size_t i = 0; i < C.value.size(); i++) {
    if (fabs(C.value[i] - c.value[i]) >=
      std::numeric_limits<double>::epsilon()) {
      check = false;
      break;
    }
  }

  ASSERT_EQ(true, check);
}

TEST(Seq, mult_random_matr_7x7) {
  int size = 7;
  std::vector<double> a = GenSpareMatrix(size);
  std::vector<double> b = GenSpareMatrix(size);
  CCS c = createCCS(size, MultMatrix(size, a, b));

  CCS A = createCCS(size, a);
  CCS B = createCCS(size, b);
  CCS C = MultCCS(TranspSpareMatrix(A), B);

  bool check = true;
  for (size_t i = 0; i < C.value.size(); i++) {
    if (fabs(C.value[i] - c.value[i]) >=
      std::numeric_limits<double>::epsilon()) {
      check = false;
      break;
    }
  }

  ASSERT_EQ(true, check);
}

TEST(Par, par_mult_zero_matr) {
  CCS A = createCCS(3, std::vector<double>(9, 0));
  CCS B = createCCS(3, std::vector<double> {
    1, 0, 3,
    0, 0, 5,
    9, 0, 0
  });
  CCS C = MultCCSParallel(TranspSpareMatrix(A), B, 4);

  ASSERT_EQ(true, C.value.empty());
}

TEST(Par, par_mult_random_matr_1x1) {
  int size = 1;
  std::vector<double> a = GenSpareMatrix(size);
  std::vector<double> b = GenSpareMatrix(size);
  CCS c = createCCS(size, MultMatrix(size, a, b));
  CCS A = createCCS(size, a);
  CCS B = createCCS(size, b);

  CCS C = MultCCS(TranspSpareMatrix(A), B);
  C = MultCCSParallel(TranspSpareMatrix(A), B, 4);

  bool check = true;
  for (size_t i = 0; i < C.value.size(); i++) {
    if (fabs(C.value[i] - c.value[i]) >=
      std::numeric_limits<double>::epsilon()) {
      check = false;
      break;
    }
  }

  ASSERT_EQ(true, check);
}

TEST(Par, par_mult_random_matr_7x7) {
  int size = 7;
  std::vector<double> a = GenSpareMatrix(size);
  std::vector<double> b = GenSpareMatrix(size);
  CCS c = createCCS(size, MultMatrix(size, a, b));
  CCS A = createCCS(size, a);
  CCS B = createCCS(size, b);

  CCS C = MultCCS(TranspSpareMatrix(A), B);
  C = MultCCSParallel(TranspSpareMatrix(A), B, 4);

  bool check = true;
  for (size_t i = 0; i < C.value.size(); i++) {
    if (fabs(C.value[i] - c.value[i]) >=
      std::numeric_limits<double>::epsilon()) {
      check = false;
      break;
    }
  }

  ASSERT_EQ(true, check);
}

TEST(Par, par_mult_random_matr_80x80) {
  int size = 80;
  std::vector<double> a = GenSpareMatrix(size);
  std::vector<double> b = GenSpareMatrix(size);
  CCS c = createCCS(size, MultMatrix(size, a, b));
  CCS A = createCCS(size, a);
  CCS B = createCCS(size, b);

  // clock_t t1 = clock();
  CCS C = MultCCS(TranspSpareMatrix(A), B);
  // clock_t t2 = clock();
  // std::cout << (t2 - t1) / (double)CLOCKS_PER_SEC << std::endl;
  // t1 = clock();
  C = MultCCSParallel(TranspSpareMatrix(A), B, 4);
  // t2 = clock();
  // std::cout << (t2 - t1) / (double)CLOCKS_PER_SEC << std::endl;
  bool check = true;
  for (size_t i = 0; i < C.value.size(); i++) {
    if (fabs(C.value[i] - c.value[i]) >=
      std::numeric_limits<double>::epsilon()) {
      check = false;
      break;
    }
  }
  ASSERT_EQ(true, check);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
