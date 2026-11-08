#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
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

// Просеивание элемента через подчиненную пирамиду
void siftDown(vector<int>& array, int heapSize, int rootIndex) {
    int childIndex = 2 * rootIndex + 1;

    while (childIndex < heapSize) {

        // Выбираем большего потомка
        if (childIndex + 1 < heapSize &&
            array[childIndex + 1] > array[childIndex]) {
            childIndex++;
        }

        // Сравниваем родителя с потомком
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

// Пирамидальная сортировка
void heapSort(vector<int>& array) {
    int size = static_cast<int>(array.size());

    // Построение максимальной пирамиды
    for (int i = size / 2 - 1; i >= 0; i--) {
        siftDown(array, size, i);
    }

    // Сортировка массива
    for (int i = size - 1; i > 0; i--) {
        swap(array[0], array[i]);

        siftDown(array, i, 0);
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
            throw runtime_error("Ошибка сортировки массива!");
        }
    }

    return totalTime / 3.0;
}

int main() {
    setlocale(LC_ALL, "Russian");

    try {
        int sizes[3] = { 10000, 100000, 1000000 };

        int minValues[3] = { -10, -1000, -100000 };
        int maxValues[3] = { 10, 1000, 100000 };

        const char* filenames[3][3] = {
            {
                "array_10000_10.txt",
                "array_10000_1000.txt",
                "array_10000_100000.txt"
            },
            {
                "array_100000_10.txt",
                "array_100000_1000.txt",
                "array_100000_100000.txt"
            },
            {
                "array_1000000_10.txt",
                "array_1000000_1000.txt",
                "array_1000000_100000.txt"
            }
        };

        // Создание файла отчета
        ofstream report("report.csv");

        if (!report.is_open()) {
            throw runtime_error("Не удалось создать report.csv");
        }

        cout << fixed << setprecision(3);

        cout << "Размер\tДиапазон\tПирамидальная сортировка"
            << endl;

        report << "Размер;Диапазон;Пирамидальная сортировка\n";

        // Обработка всех девяти тестовых массивов
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {

                vector<int> currentArray = loadArrayFromFile(
                    filenames[i][j],
                    sizes[i]
                );

                double averageTime = measureAverageTime(
                    currentArray,
                    heapSort
                );

                cout << sizes[i] << "\t["
                    << minValues[j] << ";"
                    << maxValues[j] << "]\t"
                    << averageTime << " мс"
                    << endl;

                report << sizes[i] << ";["
                    << minValues[j] << ";"
                    << maxValues[j] << "];"
                    << averageTime << "\n";
            }
        }

        report.close();

        cout << "\nРабота программы завершена успешно!" << endl;
        cout << "Отчет сохранен в report.csv" << endl;
    }
    catch (const exception& error) {
        cerr << "\nОшибка: " << error.what() << endl;
        return 1;
    }

    return 0;
}
