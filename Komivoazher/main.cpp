#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

using namespace std;

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

    void printMatrix() const {
        cout << "Cost Matrix:\n";
        for (int i = 0; i < cityCount; ++i) {
            for (int j = 0; j < cityCount; ++j) {
                cout << setw(4) << costMatrix[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
};

int main() {
    TravelingSalesperson tsp(4);
    tsp.generateRandomCosts(10, 100);
    tsp.printMatrix();
    return 0;
}