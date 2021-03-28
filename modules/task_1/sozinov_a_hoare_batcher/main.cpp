// Copyright 2021 Sozinov Alex

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "./hoare_batcher.h"

TEST(GetRandomVector, get_vector) {
  ASSERT_NO_THROW(GetRandomVector(100));
}

TEST(GetRandomVector, vector_have_correct_size) {
  std::vector<double> vect = GetRandomVector(100);
  ASSERT_EQ(static_cast<int>(vect.size()), 100);
}

TEST(Sort, can_sort) {
  std::vector<double> vect = GetRandomVector(100);
  ASSERT_NO_THROW(Sort(&vect, 0, vect.size() - 1));
}

TEST(Sort, correct_sort_100) {
  std::vector<double> vect = GetRandomVector(100);
  std::vector<double> copy = vect;
  std::sort(copy.begin(), copy.end());
  Sort(&vect, 0, vect.size() - 1);
  ASSERT_EQ(copy, vect);
}

TEST(Sort, correct_sort_41) {
  std::vector<double> vect = GetRandomVector(41);
  std::vector<double> copy = vect;
  std::sort(copy.begin(), copy.end());
  Sort(&vect, 0, vect.size() - 1);
  ASSERT_EQ(copy, vect);
}

TEST(BatcherMerge, corerct_batcher) {
  std::vector<double> res;
  std::vector<double> vectL = GetRandomVector(13);
  std::vector<double> vectR = GetRandomVector(13);
  std::vector<double> copy = vectL;

  copy.insert(copy.end(), vectR.begin(), vectR.end());
  std::sort(copy.begin(), copy.end());

  Sort(&vectL, 0, vectL.size() - 1);
  Sort(&vectR, 0, vectR.size() - 1);
  BatcherMerge(&res, vectL, vectR);
  ASSERT_EQ(copy, res);
}

TEST(BatcherMerge, corerct_batcher_dif_size) {
  std::vector<double> res;
  std::vector<double> vectL = GetRandomVector(11);
  std::vector<double> vectR = GetRandomVector(13);
  std::vector<double> copy = vectL;

  copy.insert(copy.end(), vectR.begin(), vectR.end());
  std::sort(copy.begin(), copy.end());

  Sort(&vectL, 0, vectL.size() - 1);
  Sort(&vectR, 0, vectR.size() - 1);
  BatcherMerge(&res, vectL, vectR);
  ASSERT_EQ(copy, res);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
