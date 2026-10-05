
#include <iostream>
#include <vector>
#include <numeric>
#include <random>
#include <chrono>
#include <iomanip>
#include<algorithm>

using namespace std;
using namespace std::chrono;

struct TspResult {
    int cost;
    vector<int> path;
    double executionTimeMs;
};

// алгоритм построения следующей перестановки

bool Deikstra(vector<int>& P, bool show = false) {
    int n = P.size();
    int i;

    for (i = n - 2; i >= 0; i--) {
        if (P[i] < P[i + 1]) {
            break;
        }
    }

    if (i < 0)
        return false;

    int j;
    for (j = n - 1; j > i; j--) {
        if (P[i] < P[j]) {
            break;
        }
    }

    if (show) {
        cout << "До: ";
        for (int x : P)
            cout << x << " ";
        cout << endl;
    }

    swap(P[i], P[j]);

    if (show) {
        cout << "После обмена: ";
        for (int x : P)
            cout << x << " ";
        cout << endl;
    }

    reverse(P.begin() + i + 1, P.end());

    if (show) {
        cout << "После разворота: ";
        for (int x : P)
            cout << x << " ";
        cout << endl;
    }

    return true;
}

bool DeikstraWhile(vector<int>& P) {
    int n = P.size();

    int i = n - 2;

    while (i >= 0 && P[i] >= P[i + 1]) {
        i--;
    }

    if (i < 0)
        return false;

    int j = n - 1;

    while (P[i] >= P[j]) {
        j--;
    }

    cout << "До: ";
    for (int x : P)
        cout << x << " ";
    cout << endl;

    swap(P[i], P[j]);

    cout << "После обмена: ";
    for (int x : P)
        cout << x << " ";
    cout << endl;

    int left = i + 1;
    int right = n - 1;

    while (left < right) {
        swap(P[left], P[right]);
        left++;
        right--;
    }

    cout << "После разворота: ";
    for (int x : P)
        cout << x << " ";
    cout << endl;

    return true;
}
void generateRandomCosts(
    vector<vector<int>>& costMatrix,
    int cityCount,
    int minCost,
    int maxCost) {

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(minCost, maxCost);

    for (int i = 0; i < cityCount; ++i) { //перебираем строки матрицы
        for (int j = 0; j < cityCount; ++j) { //перебираем столбцы матрицы
            if (i != j) {
                costMatrix[i][j] = dist(gen); //стоимость перехода из города i в город j.
            }
        }
    }
}

// Точный алгоритм (полный перебор)
TspResult solveExact(
    const vector<vector<int>>& costMatrix,
    int cityCount,
    int startCity,
    bool findWorst = false) { //false означает минимум

    auto startTime = high_resolution_clock::now();//засечение времен

    vector<int> citiesToVisit; // объявление динамического вектора целых чисел

    for (int i = 0; i < cityCount; ++i) { //прохождение по всем городам
        if (i != startCity)
            citiesToVisit.push_back(i); // citiesToVisit - список городов которые нужно посетить
    }

    int extremeCost = findWorst ? -1 : numeric_limits<int>::max();
    vector<int> bestPath; //лучший найденный маршрут

    do {
        int currentCost = 0;
        int currentCity = startCity;

        for (int nextCity : citiesToVisit) {
            currentCost += costMatrix[currentCity][nextCity];
            currentCity = nextCity;
        }

        currentCost += costMatrix[currentCity][startCity];

        if ((!findWorst && currentCost < extremeCost) ||
            (findWorst && currentCost > extremeCost)) {

            extremeCost = currentCost; //проверка, является ли текущий маршрут лучше сохранненого
            bestPath = citiesToVisit;
        }

    } while (Deikstra(citiesToVisit));
    // переставновка города в следующую комбинацию и продолжает перебор

    auto endTime = high_resolution_clock::now();
    duration<double, milli> durationMs = endTime - startTime;

    vector<int> fullPath = { startCity };

    fullPath.insert(
        fullPath.end(),
        bestPath.begin(),
        bestPath.end()
    );

    fullPath.push_back(startCity);

    return { extremeCost, fullPath, durationMs.count() };
}

// Жадный алгоритм (ближайший сосед)
TspResult solveHeuristicNearestNeighbor(
    const vector<vector<int>>& costMatrix,
    int cityCount,
    int startCity) {

    auto startTime = high_resolution_clock::now();

    vector<bool> visited(cityCount, false); //cityCount - сколько элементов создать false означает что город не посетили, true - обратное
    vector<int> path;// сохранением маршрута | ТОЛЬКО В VISISTED ||||

    int currentCity = startCity;
    int totalCost = 0;

    path.push_back(currentCity);
    visited[currentCity] = true;

    for (int step = 0; step < cityCount - 1; ++step) {
        int nearestCity = -1;
        int minCost = numeric_limits<int>::max();

        for (int nextCity = 0; nextCity < cityCount; ++nextCity) { //Перебирает все города в поиске следующего
            if (!visited[nextCity] &&
                costMatrix[currentCity][nextCity] < minCost) { //город ещё не посещён, стоимость перехода к нему меньше текущего минимума.

                minCost = costMatrix[currentCity][nextCity];
                nearestCity = nextCity;
            }
        }

        visited[nearestCity] = true;
        path.push_back(nearestCity);
        totalCost += minCost;
        currentCity = nearestCity;
    }

    totalCost += costMatrix[currentCity][startCity];
    path.push_back(startCity);

    auto endTime = high_resolution_clock::now();
    duration<double, milli> durationMs = endTime - startTime;

    return { totalCost, path, durationMs.count() };
}

void runExperiments(
    int cityCount,
    int minCost,
    int maxCost,
    int startCity,
    int runNumber) { //кол-во городов, мин стоимость, макс стоимость, стартовый город, номер запуска//

    vector<vector<int>> costMatrix(
        cityCount,
        vector<int>(cityCount, 0)
    );

    generateRandomCosts(
        costMatrix,
        cityCount,
        minCost,
        maxCost
    ); // генерирует рандомную стоимость заданная пользователем

    TspResult bestExact =
        solveExact(costMatrix, cityCount, startCity, false);//точный алгоритм поиска минимального маршрута

    TspResult worstExact =
        solveExact(costMatrix, cityCount, startCity, true);//точный алгоритм поиска максимального маршрута

    TspResult heuristic =
        solveHeuristicNearestNeighbor(
            costMatrix,
            cityCount,
            startCity
        ); //запуск жадного алгоритма ближайшего соседа

    double qualityPercent = 0.0;

    if (worstExact.cost != bestExact.cost) { //проверка на отличие между макс и мин стоимости

        qualityPercent =
            (static_cast<double>(worstExact.cost - heuristic.cost) /static_cast<double>(worstExact.cost - bestExact.cost)) * 100.0; //вычисление качество жадного алгоритма в %

    }
    else {
        qualityPercent = 100.0;
    }

    cout << "  Run #" << runNumber
        << " | Exact [Min: " << bestExact.cost
        << ", Max: " << worstExact.cost
        << ", Time: " << fixed << setprecision(6)
        << bestExact.executionTimeMs / 1000.0 << "s] "

        << "| Greedy [Cost: " << heuristic.cost
        << ", Time: " << fixed << setprecision(6)
        << heuristic.executionTimeMs / 1000.0 << "s] "

        << "| Quality: " << fixed << setprecision(1)
        << qualityPercent << "%\n";
}

int main() {
    setlocale(LC_ALL, "Rus");
    int startCity = 0;
    int sizes[] = { 4, 6, 8, 10, 11, 12 };


    vector<int> test1 = { 3, 4, 6, 2, 1, 5, 7 };
    vector<int> test2 = test1;

    cout << "Первый алгоритм:\n";
    Deikstra(test1, true);

    cout << "\nВторой алгоритм:\n";
    DeikstraWhile(test2);
    
    cout << "\nРезультат 1: ";
    for (int x : test1)
        cout << x << " ";

    cout << "\nРезультат 2: ";
    for (int x : test2)
        cout << x << " ";

    
    
    
    cout << "\n";
    
    cout << "Test 1. Costs from 10 to 100\n\n";

    for (int size : sizes) {

        cout << "Dimension: "
            << size << "x" << size << "\n";

        for (int run = 1; run <= 3; ++run) {
            runExperiments(size,10,100, startCity, run);
        }

        cout << "\n";
    }

    cout << "Test 2. Costs from 10 to 1000\n\n";

    for (int size : sizes) {

        cout << "Dimension: "
            << size << "x" << size << "\n";

        for (int run = 1; run <= 3; ++run) 
            runExperiments(size, 10, 1000,startCity, run);
        

        cout << "\n";
    }

    return 0;
}