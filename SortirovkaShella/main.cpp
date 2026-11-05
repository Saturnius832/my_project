#include <random>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

// Проверка отсортированного массива
bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i - 1] > arr[i]) return false;
    }
    return true;
}

// Переворот массива шагов
void reverseGaps(vector<int>& gaps) {
    int left = 0;
    int right = static_cast<int>(gaps.size()) - 1;

    while (left < right) {
        swap(gaps[left], gaps[right]);
        left++;
        right--;
    }
}

// Алгоритм Шелла
void shellSort(vector<int>& arr) {
    int n = arr.size();
    vector<int> gaps;

    for (int gap = n / 2; gap > 0; gap /= 2) {
        gaps.push_back(gap);
    }

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

// Сортировка Хиббарда
void shellSortHibbard(vector<int>& arr) {
    int n = arr.size();
    vector<int> gaps;

    for (int k = 1; ; k++) {
        long long gap = (1LL << k) - 1;

        if (gap >= n) break;

        gaps.push_back(static_cast<int>(gap));
    }

    reverseGaps(gaps);

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

    reverseGaps(gaps);

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

    reverseGaps(gaps);

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
