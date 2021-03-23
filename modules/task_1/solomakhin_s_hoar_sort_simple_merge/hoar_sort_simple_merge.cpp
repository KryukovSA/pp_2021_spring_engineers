#include "hoar_sort_simple_merge.h"
#include <random>
#include <vector>
#include <algorithm>
#include <iostream>

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
    mid = arr[(f + l) / 2]; //вычисление опорного элемента
    do
    {
        while (arr[f] < mid) 
            f++;
        while (arr[l] > mid) 
            l--;
        if (f <= l) //перестановка элементов
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

std::vector<int> merge(std::vector<int>& x, std::vector<int>& y) {
    std::vector<int> res((x.size() + y.size()));

    for (int i = 0; i < res.size(); i++) 
    {
        
    }

    return res;
}
