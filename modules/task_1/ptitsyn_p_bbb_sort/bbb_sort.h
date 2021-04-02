// Copyright 2021 Ptitsyn Pavel
#ifndef MODULES_TASK_1_PTITSYN_P_BBB_SORT_BBB_SORT_H_
#define MODULES_TASK_1_PTITSYN_P_BBB_SORT_BBB_SORT_H_

#include <vector>
#include <bitset>
#include <random>

class RandomDouble {
 public:
    static double Next();
 private:
    RandomDouble();
    std::mt19937_64 gen_;
    std::uniform_real_distribution<double> dist_;
};

std::vector<double> random_double_array(size_t size);


typedef std::vector<double>::iterator DoubleIt;
typedef std::vector<std::bitset<64>>::iterator BitsetIt;

void bitwise_sort_mod(BitsetIt first, BitsetIt last, size_t bit, bool positive);
void bitwise_sort(BitsetIt first, BitsetIt last);
void radix_sort(DoubleIt first, DoubleIt last);
std::vector<double> EvenOddBatch(std::vector<double> vec1,
    std::vector<double> vec2);
std::vector<double> evenBatch(std::vector<double> vec1,
    std::vector<double> vec2);
std::vector<double> oddBatch(std::vector<double> vec1,
    std::vector<double> vec2);
void print(std::vector<double> const& a);

#endif  // MODULES_TASK_1_PTITSYN_P_BBB_SORT_BBB_SORT_H_
