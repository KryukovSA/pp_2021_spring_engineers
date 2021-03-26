#include "../../../modules/task_1/baulin_m_radix_sort_simple_merge/radix_sort.h"

#include <algorithm>
#include <random>
#include <vector>

std::vector<double> getRandomVector(int sz) {
  std::random_device dev;
  std::mt19937 gen(dev());
  std::vector<double> vec(sz);
  for (int i = 0; i < sz; i++) {
    vec[i] = gen() % 100;
  }
  return vec;
}

std::vector<double> sort(std::vector<double> source, std::vector<double> tmp,
                         const int offset) {
  const auto const size = source.size();
  auto byteArr = (unsigned char*)source.data();
  auto acc = 0;
  int counters[256] = {0};

  for (auto i = 0; i < size; i++) {
    counters[byteArr[offset + 8 * i]]++;
  }

  for (int i = 0; i < 256; i++) {
    int tmp = counters[i];
    counters[i] = acc;
    acc += tmp;
  }

  for (auto i = 0; i < size; i++) {
    auto byteIndex = offset + 8 * i;
    auto byte = byteArr[byteIndex];
    auto counter = counters[byte];
    tmp[counter] = source[i];
    counters[byte]++;
  }

  return tmp;
}

std::vector<double> sign_sort(std::vector<double> source) {
  const auto const offset = 7;
  const auto const size = source.size();
  auto byteArr = (unsigned char*)source.data();
  auto acc = 0;

  auto result = std::vector<double>(source);
  int counters[256] = {0};

  for (auto i = 0; i < size; i++) {
    counters[byteArr[7 + 8 * i]]++;
  }

  for (int i = 255; i > 127; i--) {
    counters[i] += acc;
    acc = counters[i];
  }

  for (int i = 0; i < 128; i++) {
    int tmp = counters[i];
    counters[i] = acc;
    acc += tmp;
  }

  for (int i = 0; i < size; i++) {
    auto byteIndex = offset + 8 * i;
    auto byte = byteArr[byteIndex];
    if (byte < 128) {
      result[counters[byte]] = source[i];
      counters[byte]++;
    } else {
      counters[byte]--;
      result[counters[byte]] = source[i];
    }
  }

  return result;
}

std::vector<double> radix_sort(const std::vector<double>& source) {
  auto tmp = std::vector<double>(source.size());
  auto tmpForSwap = std::vector<double>(source.size());
  auto copy = std::vector<double>(source);

  for (int i = 0; i < 8; i++) {
    tmp = sort(copy, tmp, i);
    tmpForSwap = copy;
    copy = tmp;
    tmp = tmpForSwap;
  }

  return sign_sort(copy);
}

std::vector<double> merge(const std::vector<double>& left,
                          const std::vector<double>& right) {
  std::vector<double> result((left.size() + right.size()));

  auto i = 0, j = 0, k =0;
  for (k = 0; k < left.size() + right.size() - 1; k++)
  {
    if (left[i] < right[j])
      result[k] = left[i++];
    else
      result[k] = right[j++];
  }

  while (i < left.size()) {
    result[k++] = left[i++];
  }
  while (j < right.size()) {
    result[k++] = right[j++];
  }

  return result;
}
