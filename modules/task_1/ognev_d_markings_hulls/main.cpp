// Copyright 2021 Ognev Denis

#include <gtest/gtest.h>
#include "../../task_1/ognev_d_markings_hulls/markings_hulls.h"

TEST(Test, Marking_Test) {
  int width = 5, height = 6;
  std::vector<bool> v{true,  false, true,  false, true,  true,  true, true,
                      false, true,  false, false, false, false, true, true,
                      true,  true,  false, true,  false, false, true, false,
                      false, true,  true,  true,  false, true};
  std::vector<int> right{2, 0, 2, 0, 3, 2, 2, 2, 0, 3, 0, 0, 0, 0, 3,
                         4, 4, 4, 0, 3, 0, 0, 4, 0, 0, 4, 4, 4, 0, 6};
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (v[i * width + j] == true)
        std::cout << static_cast<char>(219);
      else
        std::cout << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
  std::vector<int> res = secondStep(firstStep(v, width, height), width, height);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      std::cout << res[i * width + j];
    }
    std::cout << "\n";
  }
  std::cout << "\n";

  ASSERT_EQ(right, res);
}
TEST(Test, Convex_Test) {
  int width = 5, height = 6;
  std::vector<bool> v{true,  false, true,  false, true,  true,  true, true,
                      false, true,  false, false, false, false, true, true,
                      true,  true,  false, true,  false, false, true, false,
                      false, true,  true,  true,  false, true};
  std::vector<int> right{135, 0, 135, 0, 137, 135, 2, 135, 0, 3,
                         0,   0, 0,   0, 3,   136, 4, 136, 0, 137,
                         0,   0, 4,   0, 0,   136, 4, 136, 0, 138};
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (v[i * width + j] == true)
        std::cout << static_cast<char>(219);
      else
        std::cout << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
  std::vector<int> res = convexHull(
      secondStep(firstStep(v, width, height), width, height), width, height);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (res[i * width + j] > 10) {
        std::cout << static_cast<char>(res[i * width + j] - 100);
      } else {
        std::cout << res[i * width + j];
      }
    }
    std::cout << "\n";
  }
  std::cout << "\n";

  ASSERT_EQ(right, res);
}
TEST(Test, First_Step_Throws_When_Width_Is_Less_Then_One) {
  std::vector<bool> v{true};
  ASSERT_ANY_THROW(firstStep(v, 0, 1));
}
TEST(Test, First_Step_Throws_When_Height_Is_Less_Then_One) {
  std::vector<bool> v{true};
  ASSERT_ANY_THROW(firstStep(v, 1, 0));
}
TEST(Test, First_Step_Throws_When_Vector_Is_Empty) {
    ASSERT_ANY_THROW(firstStep(std::vector<bool>(), 1, 1));
}
TEST(Test, Second_Step_Throws_When_Width_Is_Less_Then_One) {
  std::vector<int> v{1};
  ASSERT_ANY_THROW(secondStep(v, 0, 1));
}
TEST(Test, Second_Step_Throws_When_Height_Is_Less_Then_One) {
  std::vector<int> v{1};
  ASSERT_ANY_THROW(secondStep(v, 1, 0));
}
TEST(Test, Second_Step_Throws_When_Vector_Is_Empty) {
  ASSERT_ANY_THROW(secondStep(std::vector<int>(), 1, 1));
}
TEST(Test, Jarvis_Throws_When_Width_Is_Less_Then_One) {
  std::vector<int> v{1};
  ASSERT_ANY_THROW(jarvis(v, 0, 1, 0, 0));
}
TEST(Test, Jarvis_Throws_When_Height_Is_Less_Then_One) {
  std::vector<int> v{1};
  ASSERT_ANY_THROW(jarvis(v, 1, 0, 0, 0));
}
TEST(Test, Jarvis_Throws_When_Index_Is_Negative) {
  std::vector<int> v{1};
  ASSERT_ANY_THROW(jarvis(v, 1, 1, -1, 0));
}
TEST(Test, Jarvis_Throws_When_Mark_Is_Negative) {
  std::vector<int> v{1};
  ASSERT_ANY_THROW(jarvis(v, 1, 1, 1, -1));
}
TEST(Test, Jarvis_Throws_When_Map_Is_Empty) {
  ASSERT_ANY_THROW(jarvis(std::vector<int>(), 1, 1, 0, 0));
}
TEST(Test, Convex_Hulls_Throws_When_Width_Is_Less_Then_One) {
  std::vector<int> v(1);
  ASSERT_ANY_THROW(convexHull(v, 0, 1));
}
TEST(Test, Convex_Hulls_Throws_When_Height_Is_Less_Then_One) {
  std::vector<int> v(1);
  ASSERT_ANY_THROW(convexHull(v, 1, 0));
}
TEST(Test, Convex_Hulls_Throws_When_Vector_Is_Empty) {
  ASSERT_ANY_THROW(convexHull(std::vector<int>(), 1, 1));
}

// int main() {
//  int width = 5, height = 5;
//  std::vector<bool> bitmap = GenerateConnectedMap(width, height);
//  for (int i = 0; i < height; i++) {
//    for (int j = 0; j < width; j++) {
//      if (bitmap[i * width + j] == true)
//        std::cout << (char)219;
//      else
//        std::cout << " ";
//    }
//    std::cout << "\n";
//  }
//  std::cout << "\n";
//  std::vector<int> first = firstStep(bitmap, width, height);
//  for (int i = 0; i < height; i++) {
//    for (int j = 0; j < width; j++) {
//      std::cout << first[i * width + j];
//    }
//    std::cout << "\n";
//  }
//  std::cout << "\n";
//  std::vector<int> second = secondStep(first, width, height);
//  for (int i = 0; i < height; i++) {
//    for (int j = 0; j < width; j++) {
//      std::cout << second[i * width + j];
//    }
//    std::cout << "\n";
//  }
//  std::cout << "\n";
//  std::vector<int> borders = convexHull(second, width, height);
//  for (int i = 0; i < height; i++) {
//    for (int j = 0; j < width; j++) {
//      if (borders[i * width + j] > 10)
//        std::cout << (char)(borders[i * width + j] - 100);
//      else
//        std::cout << borders[i * width + j];
//    }
//    std::cout << "\n";
//  }
//  return 0;
// }
