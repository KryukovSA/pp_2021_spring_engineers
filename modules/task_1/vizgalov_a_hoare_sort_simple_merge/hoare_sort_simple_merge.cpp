// Copyright 2021 Vizgalov Anton

#include <random>
#include <limits>
#include <functional>
#include <algorithm>
#include <stdexcept>

#include "../../../modules/task_1/vizgalov_a_hoare_sort_simple_merge/hoare_sort_simple_merge.h"

int partition(std::vector<int>* vec, int low, int high) {
    int pivot = vec->at(high);
    int smallerElementIdx = low - 1;

    for (int i = low; i < high; ++i) {
        if (vec->at(i) < pivot) {
            std::swap(vec->at(++smallerElementIdx), vec->at(i));
        }
    }

    std::swap(vec->at(smallerElementIdx + 1), vec->at(high));

    return smallerElementIdx + 1;
}

void hoareSort(std::vector<int>* vec, int low, int high) {
    if (low < high) {
        int partitionIdx = partition(vec, low, high);

        hoareSort(vec, low, partitionIdx - 1);
        hoareSort(vec, partitionIdx + 1, high);
    }
}

void merge(std::vector<int>* vec, int left, int mid, int right) {
    int leftIdx = 0;
    int rightIdx = 0;
    int mergedIdx = left;
    int sizeLeft = mid - left + 1;
    int sizeRight = right - mid;

    while (leftIdx < sizeLeft && rightIdx < sizeRight) {
        if (vec->at(left + leftIdx) <= vec->at(mid + 1 + rightIdx)) {
            vec->at(mergedIdx) = vec->at(left + leftIdx);
            leftIdx++;
        } else {
            vec->at(mergedIdx) = vec->at(mid + 1 + rightIdx);
            rightIdx++;
        }
        mergedIdx++;
    }

    while (leftIdx < sizeLeft) {
        vec->at(mergedIdx) = vec->at(left + leftIdx);
        leftIdx++;
        mergedIdx++;
    }

    while (rightIdx < sizeRight) {
        vec->at(mergedIdx) = vec->at(mid + 1 + rightIdx);
        rightIdx++;
        mergedIdx++;
    }
}

void runHoareSort(std::vector<int>* vec) {
    int numSegments = 4;  // "nthreads" in parallel version
    int elementsPerSegment = vec->size() / numSegments + ((vec->size() % numSegments == 0) ? 0 : 1);

    for (int i = 0; i < numSegments; ++i) {
        hoareSort(vec,
                  i * elementsPerSegment,
                  std::min((i + 1) * elementsPerSegment - 1, static_cast<int>(vec->size() - 1)));
    }

    for (int i = 0; i < numSegments - 1; ++i) {
        merge(vec,
              0,
              (i + 1) * elementsPerSegment - 1,
              std::min((i + 2) * elementsPerSegment - 1, static_cast<int>(vec->size() - 1)));
    }
}

// Types:
// 0 - any integers
// 1 - only positive integers
// 2 - any integers in non-decreasing order (sorted)
// 3 - any integers in non-increasing order (reverse-sorted)
std::vector<int> getRandomVector(int size, int type) {
    std::vector<int> newVec(size);

    std::random_device dev;
    std::mt19937 randomGenerator(dev());

    if (type == 1) {
        std::uniform_int_distribution<int> randomValue(1, std::numeric_limits<int>::max());

        for (int& item : newVec) {
            item = randomValue(randomGenerator);
        }
    } else if (type >= 0 && type <= 3) {
        std::uniform_int_distribution<int> randomValue(std::numeric_limits<int>::min(),
                                                       std::numeric_limits<int>::max());

        for (int& item : newVec) {
            item = randomValue(randomGenerator);
        }

        if (type == 2) {
            sort(newVec.begin(), newVec.end());
        } else if (type == 3) {
            sort(newVec.begin(), newVec.end(), std::greater<int>());
        }
    } else {
        throw std::invalid_argument("Invalid type of vector chosen");
    }

    return newVec;
}
