#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <clocale>

using namespace std;

// Проверка, что элементы массива расположены по возрастанию
bool isSorted(const vector<int>& array) {
    for (size_t i = 1; i < array.size(); i++) {
        if (array[i - 1] > array[i]) {
            return false;
        }
    }

    return true;
}

// Восстановление свойств максимальной пирамиды
void siftDown(vector<int>& array, int heapSize, int rootIndex) {
    int childIndex = 2 * rootIndex + 1;

    while (childIndex < heapSize) {
        // Находим большего из двух потомков
        if (childIndex + 1 < heapSize &&
            array[childIndex + 1] > array[childIndex]) {
            childIndex++;
        }

        // Если потомок больше родителя, меняем их местами
        if (array[childIndex] > array[rootIndex]) {
            swap(array[rootIndex], array[childIndex]);

            rootIndex = childIndex;
            childIndex = 2 * rootIndex + 1;
        }
        else {
            break;
        }
    }
}

// Сортировка массива с помощью максимальной пирамиды
void heapSort(vector<int>& array) {
    int size = static_cast<int>(array.size());

    // Сначала строим максимальную пирамиду
    for (int i = size / 2 - 1; i >= 0; i--) {
        siftDown(array, size, i);
    }

    // Переносим максимальный элемент в конец массива
    for (int i = size - 1; i > 0; i--) {
        swap(array[0], array[i]);
        siftDown(array, i, 0);
    }
}
// Чтение массива из файла
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

// Вычисление среднего времени трех запусков сортировки
double measureAverageTime(
    const vector<int>& originalArray,
    void (*sortFunction)(vector<int>&)
) {
    double totalTime = 0;

    for (int run = 0; run < 3; run++) {
        vector<int> temporaryArray = originalArray;

        auto start = chrono::steady_clock::now();

        sortFunction(temporaryArray);

        auto end = chrono::steady_clock::now();

        chrono::duration<double, milli> duration = end - start;

        totalTime += duration.count();

        // Проверяем результат после каждого запуска
        if (!isSorted(temporaryArray)) {
            throw runtime_error("Ошибка сортировки массива!");
        }
    }

    return totalTime / 3.0;
}

int main() {
    return 0;
}