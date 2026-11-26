#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdexcept>
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
double measureAverageTime(const vector<int>& originalArray) {
    double totalTime = 0.0;

    for (int run = 0; run < 3; run++) {
        vector<int> temporaryArray = originalArray;

        auto start = chrono::steady_clock::now();

        bitwiseSort(temporaryArray);

        auto end = chrono::steady_clock::now();

        chrono::duration<double, milli> duration = end - start;

        totalTime += duration.count();

        if (!isSorted(temporaryArray)) {
            throw runtime_error("Ошибка побитовой сортировки!");
        }
    }

    return totalTime / 3.0;
}

int main() {
    setlocale(LC_ALL, "Russian");

    try {
        int size = 10000;

        vector<int> currentArray = loadArrayFromFile(
            "array_10000_10.txt",
            size
        );

        double averageTime = measureAverageTime(currentArray);

        cout << fixed << setprecision(3);

        cout << "Размер массива: " << size << endl;
        cout << "Среднее время сортировки: " << averageTime << " мс" << endl;
    }
    catch (const exception& error) {
        cerr << "\nОшибка: " << error.what() << endl;
        return 1;
    }

    return 0;
}