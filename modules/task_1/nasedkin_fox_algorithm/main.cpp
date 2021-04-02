// Copyright 2021 Nasedkin Nikita
#include <gtest/gtest.h>
#include "./fox_algorithm.h"

TEST(FoxAlgortithm, can_init_rnd_matrix) {
  ASSERT_NO_THROW(MatrixInit(4));
}

TEST(FoxAlgortithm, cant_init_wrongsize_rnd_matrix) {
  ASSERT_ANY_THROW(MatrixInit(0));
}

TEST(FoxAlgortithm, can_calc_matrix) {
  std::vector<double> a = MatrixInit(40);
  std::vector<double> b = MatrixInit(40);

  ASSERT_NO_THROW(SeqMatrixCalc(a, b, 40));
}

TEST(FoxAlgortithm, cant_calc_matrix_with_wrong_size) {
  std::vector<double> a = MatrixInit(40);
  std::vector<double> b = MatrixInit(40);

  ASSERT_ANY_THROW(SeqMatrixCalc(a, b, 5));
}

TEST(FoxAlgortithm, can_calc_block_matrix) {
  std::vector<double> a = MatrixInit(40);
  std::vector<double> b = MatrixInit(40);

  ASSERT_NO_THROW(SeqMatrixBlockCalc(a, b, 40));
}

TEST(FoxAlgortithm, cant_calc_block_matrix_with_wrong_size) {
  std::vector<double> a = MatrixInit(40);
  std::vector<double> b = MatrixInit(40);

  ASSERT_ANY_THROW(SeqMatrixBlockCalc(a, b, 5));
}

TEST(FoxAlgortithm, seq_eq_fox) {
  std::vector<double> a = MatrixInit(40);
  std::vector<double> b = MatrixInit(40);

  EXPECT_EQ(SeqMatrixCalc(a, b, 40), SeqMatrixBlockCalc(a, b, 40));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
