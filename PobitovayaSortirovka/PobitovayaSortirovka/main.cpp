#include <iostream>
#include <vector>
#include <utility>
#include <cstdint>

using namespace std;

// Проверка отсортированного массива
bool isSorted(const vector<int>& array) {
    for (size_t i = 1; i < array.size(); i++) {
        if (array[i - 1] > array[i]) {
            return false;
        }
    }

    return true;
}

// Рекурсивная часть побитовой сортировки
void bitwiseSortPart(vector<int>& array, int left, int right, int bit) {
    if (left >= right || bit < 0) {
        return;
    }

    int i = left;
    int j = right;

    uint32_t mask = 1u << bit;

    while (i <= j) {
        while (i <= j && (static_cast<uint32_t>(array[i]) & mask) == 0) {
            i++;
        }

        while (i <= j && (static_cast<uint32_t>(array[j]) & mask) != 0) {
            j--;
        }

        if (i < j) {
            swap(array[i], array[j]);
            i++;
            j--;
        }
    }

    bitwiseSortPart(array, left, j, bit - 1);
    bitwiseSortPart(array, i, right, bit - 1);
}

// Основная побитовая сортировка
void bitwiseSort(vector<int>& array) {
    if (array.empty()) {
        return;
    }

    int maxValue = 0;

    for (int number : array) {
        if (number > maxValue) {
            maxValue = number;
        }
    }

    int highestBit = -1;

    while (maxValue > 0) {
        highestBit++;
        maxValue >>= 1;
    }

    bitwiseSortPart(array, 0, static_cast<int>(array.size()) - 1, highestBit);
}

int main() {
    vector<int> array = { 6, 3, 12, 1, 9, 4, 14, 7 };

    bitwiseSort(array);

    for (int number : array) {
        cout << number << " ";
    }

    cout << endl;

    return 0;
}