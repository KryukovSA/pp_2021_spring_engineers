// Copyright 2021 Ivanov Yaroslav
#include <random>
#include <ctime>
#include <algorithm>
#include <vector>
#include "../../../modules/task_1/ivanov_y_double_sort/sort_double.h"

double* BubbleForCompare(double* inputNumbers, int size) {
    double* numbers = inputNumbers;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (numbers[i] > numbers[j]) {
                double tmp = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = tmp;
            }
        }
    }
    return numbers;
    delete[] numbers;
}

double* generateDouble(int n) {
    std::mt19937 gen;
    gen.seed(static_cast<int>(time(0)));
    double* vec = new double[n];
    for (int i = 0; i < n; i++) {
        double numb = gen() / 1000;
        while (numb >= 1001 || numb <= -1001) {
            numb /= 100;
        }
        vec[i] = numb;
    }
    return vec;
}

void transit(double* inputNumbers, double* loc, int size, int add) {
    unsigned char* pmem = (unsigned char*)inputNumbers;
    int counters[256];
    int sum = 0;

    for (int i = 0; i < 256; i++) {
        counters[i] = 0;
    }
    for (int i = 0; i < size; i++) {
        counters[pmem[8 * i + add]]++;
    }
    for (int i = 0; i < 256; i++) {
        int tmp = counters[i];
        counters[i] = sum;
        sum += tmp;
    }
    for (int i = 0; i < size; i++) {
        int index = 8 * i + add;
        loc[counters[pmem[index]]] = inputNumbers[i];
        counters[pmem[index]]++;
    }
}

void transit1(double* inputNumbers, double* loc, int size, int add) {
    unsigned char* pmem = (unsigned char*)inputNumbers;
    int counters[256];
    int sum = 0;

    for (int i = 0; i < 256; i++) {
        counters[i] = 0;
    }

    for (int i = 255; i > 127; i--) {
        counters[i] += sum;
        sum = counters[i];
    }

    for (int i = 0; i < 128; i++) {
        int tmp = counters[i];
        counters[i] = sum;
        sum += tmp;
    }

    for (int i = 0; i < size; i++) {
        int index = 8 * i + add;
        if (pmem[index] < 128) {
            loc[counters[pmem[index]]] = inputNumbers[i];
            counters[pmem[index]]++;
        } else {
            counters[pmem[index]]--;
            loc[counters[pmem[index]]] = inputNumbers[i];
        }
    }
}

void loc_sort(double* inputNumbers, int size) {
    double* tmp = nullptr;
    double* loc = new double[size];
    for (int i = 0; i < 8; i++) {
        transit(inputNumbers, loc, size, i);
        tmp = inputNumbers;
        inputNumbers = loc;
        loc = tmp;
    }
    transit1(inputNumbers, loc, size, 7);
    delete[] tmp;
}
