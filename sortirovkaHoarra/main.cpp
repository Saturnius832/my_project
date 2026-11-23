#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <clocale>
#include <utility>

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
    // Если фрагмент состоит из одного элемента или пуст
    if (left >= right) {
        return;
    }

    // Установка указателей и выбор опорного элемента
    int i = left;
    int j = right;
    int x = array[(left + right) / 2];

    // Разделение массива на два фрагмента
    while (i <= j) {

        // Двигаемся слева направо
        while (i <= right && array[i] < x) {
            i++;
        }

        // Двигаемся справа налево
        while (j >= left && array[j] > x) {
            j--;
        }

        // Обмен элементов
        if (i <= j) {
            swap(array[i], array[j]);

            i++;
            j--;
        }
    }

    // Сортировка левого фрагмента
    if (left < j) {
        quickSortPart(array, left, j);
    }

    // Сортировка правого фрагмента
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
        ofstream reportQuickSort("reportQuickSort.csv");

        if (!reportQuickSort.is_open()) {
            throw runtime_error("Не удалось создать reportQuickSort.csv");
        }

        cout << fixed << setprecision(3);

        cout << "Размер\tДиапазон\tБыстрая сортировка Хоара"
            << endl;

        reportQuickSort << "Размер;Диапазон;Быстрая сортировка Хоара\n";

        // Обработка всех девяти тестовых массивов
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {

                vector<int> currentArray = loadArrayFromFile(
                    filenames[i][j],
                    sizes[i]
                );

                double averageTime = measureAverageTime(
                    currentArray,
                    quickSort
                );

                cout << sizes[i] << "\t["
                    << minValues[j] << ";"
                    << maxValues[j] << "]\t"
                    << averageTime << " мс"
                    << endl;

                reportQuickSort << sizes[i] << ";["
                    << minValues[j] << ";"
                    << maxValues[j] << "];"
                    << averageTime << "\n";
            }
        }

        reportQuickSort.close();

        cout << "\nРабота программы завершена успешно!" << endl;
        cout << "Отчет сохранен в reportQuickSort.csv" << endl;
    }
    catch (const exception& error) {
        cerr << "\nОшибка: " << error.what() << endl;
        return 1;
    }

    return 0;
}