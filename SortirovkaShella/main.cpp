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
void shellSortOriginal(vector<int>& arr) {
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

