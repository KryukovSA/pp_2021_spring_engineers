#include "../../../modules/task_1/solomakhin_s_hoar_sort_simple_merge/hoar_sort_simple_merge.h"
#include <random>
#include <algorithm>
#include <vector>

std::vector<int> random_gen(int size)
{
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<int> vec(size);
    for (int i = 0; i < size; i++)
    {
        vec[i] = gen() % 100;
    }
    return vec;
}

std::vector<int> hoar_sort(std::vector<int>& arr, int first, int last)
{
    int mid, count;
    int f = first, l = last;
    mid = static_cast<int>(arr[(f + l) / 2]);
    do
    {
        while (arr[f] < mid)
            f++;
        while (arr[l] > mid)
            l--;
        if (f <= l)
        {
            count = arr[f];
            arr[f] = arr[l];
            arr[l] = count;
            f++;
            l--;
        }
    } while (f < l);
    if (first < l) hoar_sort(arr, first, l);
    if (f < last) hoar_sort(arr, f, last);

    return arr;
}

std::vector<int> merge(std::vector<int>& a, std::vector<int>& b) {
    std::vector<int> result((a.size() + b.size()));

    int i = 0, j = 0, k = 0;
    while (i < static_cast<int>(a.size()) && j < static_cast<int>(b.size())) {
        if (a[i] < b[j])
            result[k] = a[i++];
        else
            result[k] = b[j++];
        k++;
    }
    while (i < static_cast<int>(a.size())) {
        result[k++] = a[i++];
    }
    while (j < static_cast<int>(b.size())) {
        result[k++] = b[j++];
    }

    return result;
}
