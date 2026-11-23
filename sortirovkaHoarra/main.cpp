#include <iostream>
#include <vector>
#include <utility>
#include <chrono>
#include <fstream>
#include <string>
#include <stdexcept>

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

// Загрузка массива из файла
vector<int> loadArrayFromFile(const string& filename, int size) {
    ifstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл: " + filename);
    }

    vector<int> array(size);

    for (int i = 0; i < size; i++) {
        if (!(file >> array[i])) {
            throw runtime_error("Ошибка чтения файла: " + filename);
        }
    }

    return array;
}

// Измерение среднего времени трех запусков
double measureAverageTime(
    const vector<int>& originalArray,
    void (*sortFunction)(vector<int>&)
) {
    double totalTime = 0;

    for (int run = 0; run < 3; run++) {

        // Создаем копию исходного массива
        vector<int> temporaryArray = originalArray;

        auto start = chrono::steady_clock::now();

        sortFunction(temporaryArray);

        auto end = chrono::steady_clock::now();

        chrono::duration<double, milli> duration = end - start;

        totalTime += duration.count();

        // Проверяем правильность сортировки
        if (!isSorted(temporaryArray)) {
            throw runtime_error("Ошибка быстрой сортировки!");
        }
    }

    return totalTime / 3.0;
}