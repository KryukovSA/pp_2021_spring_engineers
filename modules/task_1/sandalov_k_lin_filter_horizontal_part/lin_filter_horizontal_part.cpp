// Copyright 2020 Sandalov Konstantin
#include <cstdint>
#include <cmath>
#include <vector>
#include <stdexcept>
#include "../../modules/task_1/sandalov_k_lin_filter_horizontal_part/lin_filter_horizontal_part.h"


namespace my {
    int64_t clamp(int64_t val, int64_t min, int64_t max) {
        if (val < min) return min;
        if (val > max) return max;
        return val;
    }

    std::vector<float> createGaussianFilter(int64_t N, double sigma) {
        if (N % 2 == 0) {
            throw std::runtime_error("Kernel size should be odd");
        }
        if (N <= 0) {
            throw std::runtime_error("Kernel size should be positive");
        }
        if (sigma <= 0) {
            throw std::runtime_error("Sigma should be positive");
        }

        std::vector<float> imgFilter(N*N);
        int64_t n = N / 2;
        float sum{};
        for (int64_t i = -n; i <= n; ++i) {
            for (int64_t j = -n; j <= n; ++j) {
                double r = (i * i + j * j);
                double s{ 2.0 * sigma * sigma };

                imgFilter[(n + i) * N + (n + j)] = static_cast<float>
                    (exp(-(r / s)) / (3.14 * s));
                sum += imgFilter[(n + i) * N + (n + j)];
            }
        }
        for (int64_t i = 0; i < N; ++i) {
            for (int64_t j = 0; j < N; ++j) {
                imgFilter[i * N + j] /= sum;
            }
        }
        return imgFilter;
    }

    float applyKernel(const std::vector<float>& srcImg,
        const std::vector<float>& kernel, int64_t X,
                                            int64_t Y,
                                            int64_t N,
                                            int64_t M,
                                            int64_t K) {
        float resValue{0};
        int64_t width = K / 2;
        for (int64_t i = -width; i <= width; ++i) {
            for (int64_t j = -width; j <= width; ++j) {
                int64_t curX = clamp(X + i, 0, N - 1);
                int64_t curY = clamp(Y + j, 0, M - 1);
                resValue += static_cast<float>(srcImg[(curX)*M + (curY)]
                    * kernel[(width + i) * K + (width + j)]);
            }
        }
        return resValue;
    }

    std::vector<float> linearFilterSeq(const std::vector<float>& srcImg,
        const std::vector<float>& kernel, int64_t N, int64_t M, int64_t K) {
        if (N <= 0 || M <= 0 || K <= 0) {
            throw std::runtime_error("Arguments should be positive");
        }
        if (srcImg.size() != static_cast<size_t>(N*M)) {
            throw std::runtime_error("Incorrect Image Size");
        }
        if (kernel.size() != static_cast<size_t>(K*K)) {
            throw std::runtime_error("Incorrect Kernel Size");
        }
        std::vector<float> resImg(N * M);
        for (int64_t i = 0; i < K; ++i) {
            for (int64_t j = i; j < N; j += K) {
                for (int64_t f = 0; f < M; ++f) {
                    resImg[j * M + f] = applyKernel(srcImg,
                        kernel, j, f, N, M, K);
                }
            }
        }
        return resImg;
    }
}  // namespace my
