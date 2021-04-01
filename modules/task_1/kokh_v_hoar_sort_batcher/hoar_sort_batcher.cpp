// Copyright 2021 Kokh Vladislav
#include <random>
#include <ctime>
#include "../../modules/task_1/kokh_v_hoar_sort_batcher/hoar_sort_batcher.h"


double* randomFunc(int n) {
    std::mt19937 gen(time(0));
    std::uniform_int_distribution <int> dist(-500, 500);
    double* mas = new double[n];
    for (int i = 0; i < n; ++i) {
        mas[i] = dist(gen);
    }
    return mas;
}

void sortFunc(int l, int r, double* mas) {
    int l_frame, r_frame;
    double razr_el, tmp;
    while (r > l) {
        l_frame = l;
        r_frame = r;
        razr_el = mas[(l + r) / 2];
        while (l_frame <= r_frame) {
            while (mas[l_frame] < razr_el) {
                l_frame++;
            }
            while (mas[r_frame] > razr_el) {
                r_frame--;
            }
            if (l_frame <= r_frame) {
                tmp = mas[l_frame];
                mas[l_frame] = mas[r_frame];
                mas[r_frame] = tmp;
                l_frame++;
                r_frame--;
            }
        }
        if (2 * l_frame > l + r) {
            sortFunc(l_frame, r, mas);
            r = l_frame - 1;
        } else {
            sortFunc(l, l_frame - 1, mas);
            l = l_frame;
        }
    }
}


bool check(double* mas, int n) {
    bool flag = true;
    for (int i = 0; i < n - 1; i++) {
        if (mas[i] > mas[i + 1]) {
            flag = false;
            break;
        }
    }
    return flag;
}
