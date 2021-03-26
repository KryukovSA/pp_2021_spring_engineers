#include <vector>

std::vector<double> getRandomVector(int size);
std::vector<double> sort(std::vector<double> vec1, std::vector<double> vec2,
                         int byteNum);
std::vector<double> negative_sort(std::vector<double> source, int offset);
std::vector<double> radix_sort(const std::vector<double>& vec);
std::vector<double> merge(const std::vector<double>& a,
                          const std::vector<double>& b);
