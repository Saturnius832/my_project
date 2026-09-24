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
                if (i != j) costMatrix[i][j] = dist(gen);
            }
        }
    }

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
};

int main() {
    TravelingSalesperson tsp(6);
    tsp.generateRandomCosts(10, 100);
    TspResult res = tsp.solveExact(0);
    cout << "Exact best cost: " << res.cost << " in " << res.executionTimeMs << " ms\n";
    return 0;
}