#include <random>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

// Проверка отсортированного массива
bool ProverkaSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i - 1] > arr[i]) return false;
    }
    return true;
}

// Переворот массива шагов
void perevorotGaps(vector<int>& gaps) {
    int left = 0;
    int right = static_cast<int>(gaps.size()) - 1;

    while (left < right) {
        swap(gaps[left], gaps[right]);
        left++;
        right--;
    }
}

void shellSort(vector<int>& a) {
    int n = static_cast<int>(a.size());

    vector<int> h;
    for (int g = n / 2; g > 0; g /= 2) {
        h.push_back(g);
    }

    int t = static_cast<int>(h.size()) - 1;

    for (int i = 0; i <= t; i++) {
        int s = h[i];

        for (int b = 0; b < s; b++) {

            for (int j = b + s; j < n; j += s) {
                int x = a[j];
                int k = j - s;

                while (k >= 0 && a[k] > x) {
                    a[k + s] = a[k];
                    k = k - s;
                }

                a[k + s] = x;
            }
        }
    }
}


// Сортировка Хиббарда
void shellSortHibbard(vector<int>& arr) {
    int n = arr.size();
    vector<int> gaps;

    for (int k = 1; ; k++) {
        long long gap = (1LL << k) - 1;

        if (gap >= n) break;

        gaps.push_back(static_cast<int>(gap));
    }

    perevorotGaps(gaps);

    int t = static_cast<int>(gaps.size()) - 1;

    for (int i = 0; i <= t; i++) {
        int s = gaps[i];

        for (int b = 0; b < s; b++) {
            for (int j = b + s; j < n; j += s) {
                int x = arr[j];
                int k = j - s;

                while (k >= 0 && arr[k] > x) {
                    arr[k + s] = arr[k];
                    k = k - s;
                }

                arr[k + s] = x;
            }
        }
    }
}

// Сортировка Кнута
void shellSortKnuth(vector<int>& arr) {
    int n = arr.size();
    vector<int> gaps;

    int gap = 1;

    while (gap < n) {
        gaps.push_back(gap);
        gap = 3 * gap + 1;
    }

    perevorotGaps(gaps);

    int t = static_cast<int>(gaps.size()) - 1;

    for (int i = 0; i <= t; i++) {
        int s = gaps[i];

        for (int b = 0; b < s; b++) {
            for (int j = b + s; j < n; j += s) {
                int x = arr[j];
                int k = j - s;

                while (k >= 0 && arr[k] > x) {
                    arr[k + s] = arr[k];
                    k = k - s;
                }

                arr[k + s] = x;
            }
        }
    }
}

// Сортировка Сэджвика

void shellSortSedgewick(vector<int>& arr) {
    int n = arr.size();
    vector<int> gaps;

    for (int k = 0; ; k++) {
        long long gap;

        if (k % 2 == 0) {
            int p = k / 2;
            gap = 9LL * (1LL << (2 * p)) - 9LL * (1LL << p) + 1;
        }
        else {
            int p = (k - 1) / 2;
            gap = 8LL * (1LL << (2 * p + 1)) - 6LL * (1LL << (p + 1)) + 1;
        }

        if (gap >= n) break;

        gaps.push_back(static_cast<int>(gap));
    }

    perevorotGaps(gaps);

    for (int i = 0; i < static_cast<int>(gaps.size()); i++) {
        int s = gaps[i];

        for (int b = 0; b < s; b++) {
            for (int j = b + s; j < n; j += s) {
                int x = arr[j];
                int k = j - s;

                while (k >= 0 && arr[k] > x) {
                    arr[k + s] = arr[k];
                    k = k - s;
                }

                arr[k + s] = x;
            }
        }
    }
}
// Генерация случайных массивов
void generateAndSaveArray(int size, int minVal, int maxVal, const char* filename) {
    static mt19937 gen(random_device{}());
    uniform_int_distribution<int> dis(minVal, maxVal);

    ofstream fout(filename);

    for (int i = 0; i < size; i++) {
        fout << dis(gen) << " ";
    }

    fout.close();
}

// Загрузка массива из файла
vector<int> loadArrayFromFile(const char* filename, int size) {
    vector<int> arr(size);
    ifstream fin(filename);

    for (int i = 0; i < size; i++) {
        fin >> arr[i];
    }

    fin.close();
    return arr;
}

// Среднее время трех запусков
double measureAverageTime(const vector<int>& originalArr,
    void (*sortFunc)(vector<int>&)) {

    double totalTime = 0;

    for (int run = 0; run < 3; run++) {
        vector<int> tempArr = originalArr;

        auto start = chrono::high_resolution_clock::now();

        sortFunc(tempArr);

        auto end = chrono::high_resolution_clock::now();

        if (!ProverkaSorted(tempArr)) {
            cout << "Ошибка сортировки!" << endl;
        }

        chrono::duration<double, milli> duration = end - start;
        totalTime += duration.count();
    }

    return totalTime / 3.0;
}

int main() {
    setlocale(LC_ALL, "Russian");

    int sizes[3] = { 10000, 100000, 1000000 };
    int minVals[3] = { -10, -1000, -100000 };
    int maxVals[3] = { 10, 1000, 100000 };

    const char* filenames[3][3] = {
        {"array_10000_10.txt", "array_10000_1000.txt", "array_10000_100000.txt"},
        {"array_100000_10.txt", "array_100000_1000.txt", "array_100000_100000.txt"},
        {"array_1000000_10.txt", "array_1000000_1000.txt", "array_1000000_100000.txt"}
    };

    // Генерация массивов
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            ifstream check(filenames[i][j]);

            if (!check) {
                generateAndSaveArray(
                    sizes[i], minVals[j], maxVals[j], filenames[i][j]
                );
            }

            check.close();
        }
    }

    ofstream report("report.csv");

    cout << fixed << setprecision(3);

    cout << "Размер\tДиапазон\tШелла\tХиббарда\tКнута\tСэджвика" << endl;

    report << "Размер;Диапазон;Шелла;Хиббарда;Кнута;Сэджвика\n";

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {

            vector<int> currentArray = loadArrayFromFile(
                filenames[i][j], sizes[i]
            );

            double tShell = measureAverageTime(currentArray, shellSort);
            double tHibbard = measureAverageTime(currentArray, shellSortHibbard);
            double tKnuth = measureAverageTime(currentArray, shellSortKnuth);
            double tSedgewick = measureAverageTime(currentArray, shellSortSedgewick);

            cout << sizes[i] << "\t[" << minVals[j] << ";" << maxVals[j] << "]\t"
                << tShell << "\t" << tHibbard << "\t"
                << tKnuth << "\t" << tSedgewick << endl;

            report << sizes[i] << ";[" << minVals[j] << ";" << maxVals[j] << "];"
                << tShell << ";" << tHibbard << ";"
                << tKnuth << ";" << tSedgewick << "\n";
        }
    }

    report.close();

    return 0;
}
