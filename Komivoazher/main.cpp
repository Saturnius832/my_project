#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

struct TspResult {
    int cost;
    vector<int> path;
    double executionTimeMs;
};

class TravelingSalesperson {
private:
    int cityCount;
    vector<vector<int>> costMatrix;

public:
    TravelingSalesperson(int n) : cityCount(n) {
        costMatrix.assign(n, vector<int>(n, 0));
    }

    void generateRandomCosts(int minCost, int maxCost) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(minCost, maxCost);
        for (int i = 0; i < cityCount; ++i) {
            for (int j = 0; j < cityCount; ++j) {
                if (i != j) {
                    costMatrix[i][j] = dist(gen);
                }
            }
        }
    }

    // Точный алгоритм (полный перебор)
    TspResult solveExact(int startCity, bool findWorst = false) const {
        auto startTime = high_resolution_clock::now();
        vector<int> citiesToVisit;
        for (int i = 0; i < cityCount; ++i) {
            if (i != startCity) citiesToVisit.push_back(i);
        }

        int extremeCost = findWorst ? -1 : numeric_limits<int>::max();
        vector<int> bestPath;

        do {
            int currentCost = 0;
            int currentCity = startCity;
            for (int nextCity : citiesToVisit) {
                currentCost += costMatrix[currentCity][nextCity];
                currentCity = nextCity;
            }
            currentCost += costMatrix[currentCity][startCity];

            if ((!findWorst && currentCost < extremeCost) || (findWorst && currentCost > extremeCost)) {
                extremeCost = currentCost;
                bestPath = citiesToVisit;
            }
        } while (next_permutation(citiesToVisit.begin(), citiesToVisit.end()));

        auto endTime = high_resolution_clock::now();
        duration<double, milli> durationMs = endTime - startTime;

        vector<int> fullPath = { startCity };
        fullPath.insert(fullPath.end(), bestPath.begin(), bestPath.end());
        fullPath.push_back(startCity);

        return { extremeCost, fullPath, durationMs.count() };
    }

    // Жадный алгоритм (ближайший сосед)
    TspResult solveHeuristicNearestNeighbor(int startCity) const {
        auto startTime = high_resolution_clock::now();
        vector<bool> visited(cityCount, false);
        vector<int> path;

        int currentCity = startCity;
        int totalCost = 0;

        path.push_back(currentCity);
        visited[currentCity] = true;

        for (int step = 0; step < cityCount - 1; ++step) {
            int nearestCity = -1;
            int minCost = numeric_limits<int>::max();

            for (int nextCity = 0; nextCity < cityCount; ++nextCity) {
                if (!visited[nextCity] && costMatrix[currentCity][nextCity] < minCost) {
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
};

void runExperiments(int cityCount, int minCost, int maxCost, int startCity, int runNumber) {
    TravelingSalesperson tsp(cityCount);
    tsp.generateRandomCosts(minCost, maxCost);

    TspResult bestExact = tsp.solveExact(startCity, false);
    TspResult worstExact = tsp.solveExact(startCity, true);
    TspResult heuristic = tsp.solveHeuristicNearestNeighbor(startCity);

    double qualityPercent = 0.0;
    if (worstExact.cost != bestExact.cost) {
        qualityPercent = (static_cast<double>(worstExact.cost - heuristic.cost) /
            static_cast<double>(worstExact.cost - bestExact.cost)) * 100.0;
    }
    else {
        qualityPercent = 100.0;
    }

    cout << "  Run #" << runNumber
        << " | Exact [Min: " << bestExact.cost << ", Max: " << worstExact.cost
        << ", Time: " << fixed << setprecision(6) << bestExact.executionTimeMs / 1000.0 << "s] "
        << "| Greedy [Cost: " << heuristic.cost
        << ", Time: " << fixed << setprecision(6) << heuristic.executionTimeMs / 1000.0 << "s] "
        << "| Quality: " << fixed << setprecision(1) << qualityPercent << "%\n";
}

int main() {
    int startCity = 0;
    int sizes[] = { 4, 6, 8, 10, 11, 12 };

    cout << "Test 1. Costs from 10 to 100\n\n";
    for (int size : sizes) {
        cout << "Dimension: " << size << "x" << size << "\n";
        for (int run = 1; run <= 3; ++run) {
            runExperiments(size, 10, 100, startCity, run);
        }
        cout << "\n";
    }

    cout << "Test 2. Costs from 10 to 1000\n\n";
    for (int size : sizes) {
        cout << "Dimension: " << size << "x" << size << "\n";
        for (int run = 1; run <= 3; ++run) {
            runExperiments(size, 10, 1000, startCity, run);
        }
        cout << "\n";
    }

    return 0;
}