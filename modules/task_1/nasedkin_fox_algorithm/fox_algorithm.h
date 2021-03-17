// Copyright 2021 Nasedkin Nikita
#ifndef MODULES_TASK_1_NASEDKIN_FOX_ALGORITHM_FOX_ALGORITHM_H_
#define MODULES_TASK_1_NASEDKIN_FOX_ALGORITHM_FOX_ALGORITHM_H_

#define procCount 2
#include <vector>

std::vector<double> MatrixInit(int size);
std::vector<double> SeqMatrixCalc(std::vector<double> a,
  std::vector<double> b, int size);
std::vector<double> SeqMatrixBlockCalc(std::vector<double> a,
  std::vector<double> b, int blockSize);

#endif  // MODULES_TASK_1_NASEDKIN_FOX_ALGORITHM_FOX_ALGORITHM_H_
