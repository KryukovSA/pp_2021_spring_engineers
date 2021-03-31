// Copyright 2021 Ekaterina Burmistrova

#include <omp.h>
#include <vector>
#include <string>
#include <random>
#include <iostream>
#include <functional>
#include "./../../modules/task_1/bourmistrova_e_tr_int/trapezoid_integral.h"

double SolveParallel(std::vector<std::pair<int, std::pair<int, int>>>
    ord_and_bord,
    std::function<double(double, double, double)> f) {
    int num_threads = omp_get_num_threads();
    double tr_sum = 0;
    int i = 0, j = 0, k = 0;
    if (ord_and_bord.size() == 1) {  // ONE DIMENSION
        std::cout << num_threads << "\n";
        // int h = (ord_and_bord[0].second.second
        // - ord_and_bord[0].second.first) / num_threads;
        int h = 1;
        #pragma omp parallel for private(i) reduction(+ : tr_sum)
        for (i = ord_and_bord[0].second.first;
            i < ord_and_bord[0].second.second; i++) {
            if (i + h > ord_and_bord[0].second.second)
                h = ord_and_bord[0].second.second - i;
            tr_sum += ((f(i, 1, 1) + f(i + h, 1, 1)) / 2) * h;
        }
    } else if (ord_and_bord.size() == 2) {  // TWO DIMENSIONS
        double q = 1;
        // int h1 = (ord_and_bord[0].second.second
        // - ord_and_bord[0].second.first) / num_threads;
        // int h2 = (ord_and_bord[1].second.second
        // - ord_and_bord[1].second.first) / num_threads;
        int h1 = 1, h2 = 1;
        int delta2 = h2;
        int delta1 = h1;
        // int delta1 = h1, delta2 = h2;
        int num_threads = omp_get_num_threads();
        std::cout << num_threads << "\n";
        #pragma omp parallel for private(i, j, q) reduction(+ : tr_sum)
        for (i = ord_and_bord[0].second.first;
            i < ord_and_bord[0].second.second+1; i++) {
            if (i + h1 > ord_and_bord[0].second.second)
                h1 = ord_and_bord[0].second.second - i;
            h2 = delta2;
            for (j = ord_and_bord[1].second.first;
                j < ord_and_bord[1].second.second+1; j++) {
                if (j + h2 > ord_and_bord[1].second.second)
                    h2 = ord_and_bord[1].second.second - j;
                if ((i == ord_and_bord[0].second.first ||
                    i == ord_and_bord[0].second.second) &&
                   (j == ord_and_bord[1].second.first ||
                    j == ord_and_bord[1].second.second))
                    q = 0.25;
                else if (((i == ord_and_bord[0].second.first ||
                    i == ord_and_bord[0].second.second) &&
                    (j != ord_and_bord[1].second.first &&
                     j != ord_and_bord[1].second.second))||
                    ((j == ord_and_bord[1].second.first ||
                     j == ord_and_bord[1].second.second) &&
                    (i != ord_and_bord[0].second.first &&
                     i != ord_and_bord[0].second.second)))
                    q = 0.5;
                tr_sum += q * f(i, j, 1);
                q = 1;
            }
        }
        tr_sum = delta1 * delta2 * tr_sum;
    } else {  // THREE DIMENSIONS
        double q = 1;
        // int h1 = (ord_and_bord[0].second.second
        // - ord_and_bord[0].second.first) / num_threads;
        // int h2 = (ord_and_bord[1].second.second
        // - ord_and_bord[1].second.first) / num_threads;
        // int h3 = (ord_and_bord[2].second.second
        // - ord_and_bord[2].second.first) / num_threads;
        int h1 = 1, h2 = 1, h3 = 1;
        // int delta3 = h3;
        // int delta2 = h2;
        // int delta1 = h1;
        // int delta1 = h1, delta2 = h2;
        #pragma omp parallel for private(i, j, k) reduction(+ : tr_sum)
        for (i = ord_and_bord[0].second.first;
            i < ord_and_bord[0].second.second + 1; i++) {
            // if (i + h1 > ord_and_bord[0].second.second)
                 // h1 = ord_and_bord[0].second.second - i
            // h3 = delta3;
            for (j = ord_and_bord[1].second.first;
                j < ord_and_bord[1].second.second + 1; j++) {
                // if (j + h2 > ord_and_bord[1].second.second)
                    // h2 = ord_and_bord[1].second.second - j;
                // h2 = delta2;
                for (k = ord_and_bord[2].second.first;
                    k < ord_and_bord[2].second.second + 1; k++) {
                    // if (k + h3 > ord_and_bord[2].second.second)
                         // h3 = ord_and_bord[2].second.second - k;
                    q = 1;
                    if ((i == ord_and_bord[0].second.first ||
                        i == ord_and_bord[0].second.second) &&
                        (j == ord_and_bord[1].second.first ||
                            j == ord_and_bord[1].second.second) &&
                            (k == ord_and_bord[2].second.first ||
                                k == ord_and_bord[2].second.second)) {
                        q = 0.125;
                    } else if (((i == ord_and_bord[0].second.first ||
                        i == ord_and_bord[0].second.second) &&
                        (k == ord_and_bord[2].second.first ||
                            k == ord_and_bord[2].second.second) &&
                            (j != ord_and_bord[1].second.first &&
                                j != ord_and_bord[1].second.second)) ||
                                ((j == ord_and_bord[1].second.first ||
                                    j == ord_and_bord[1].second.second) &&
                                    (i == ord_and_bord[0].second.first ||
                                        i == ord_and_bord[0].second.second) &&
                                        (k != ord_and_bord[2].second.first &&
                                       k != ord_and_bord[2].second.second)) ||
                                       ((k == ord_and_bord[2].second.first ||
                                       k == ord_and_bord[2].second.second) &&
                                       (j == ord_and_bord[1].second.first ||
                                       j == ord_and_bord[1].second.second) &&
                                       (i != ord_and_bord[0].second.first &&
                                       i != ord_and_bord[0].second.second))) {
                        q = 0.25;
                    } else if (((i == ord_and_bord[0].second.first ||
                        i == ord_and_bord[0].second.second) &&
                        (k != ord_and_bord[2].second.first &&
                            k != ord_and_bord[2].second.second) &&
                            (j != ord_and_bord[1].second.first &&
                                j != ord_and_bord[1].second.second)) ||
                                ((j == ord_and_bord[1].second.first ||
                                    j == ord_and_bord[1].second.second) &&
                                    (i != ord_and_bord[0].second.first &&
                                        i != ord_and_bord[0].second.second) &&
                                        (k != ord_and_bord[2].second.first &&
                                        k != ord_and_bord[2].second.second)) ||
                                        ((k == ord_and_bord[2].second.first ||
                                        k == ord_and_bord[2].second.second) &&
                                        (j != ord_and_bord[1].second.first &&
                                        j != ord_and_bord[1].second.second) &&
                                        (i != ord_and_bord[0].second.first &&
                                        i != ord_and_bord[0].second.second))) {
                        q = 0.5;
                    }
                tr_sum += q * f(i, j, k);
                }
            }
        }
        tr_sum = h1 * h2 * h3 * tr_sum;
    }

    return tr_sum;
}
