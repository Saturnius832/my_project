#include <iostream>
#include <vector>
#include <utility>

using namespace std;

// Рекурсивная часть быстрой сортировки Хоара_3
void quickSortPart(vector<int>& array, int left, int right) {
    if (left >= right) {
        return;
    }

    int i = left;
    int j = right;
    int x = array[(left + right) / 2];

    while (i <= j) {
        while (i <= right && array[i] < x) {
            i++;
        }

        while (j >= left && array[j] > x) {
            j--;
        }

        if (i <= j) {
            swap(array[i], array[j]);

            i++;
            j--;
        }
    }

    if (left < j) {
        quickSortPart(array, left, j);
    }

    if (i < right) {
        quickSortPart(array, i, right);
    }
}

// Быстрая сортировка Хоара
void quickSort(vector<int>& array) {
    if (!array.empty()) {
        quickSortPart(array, 0, static_cast<int>(array.size()) - 1);
    }
}