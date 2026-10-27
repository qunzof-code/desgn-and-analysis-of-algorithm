//25/DA/003
//ABHISHEK
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Recursive helper function to print the optimal parenthesization
void printParenthesization(int i, int j, const vector<vector<int>>& split) {
    if (i == j) {
        cout << "A" << i;
        return;
    }
    cout << "(";
    printParenthesization(i, split[i][j], split);
    printParenthesization(split[i][j] + 1, j, split);
    cout << ")";
}

// Function to solve Matrix Chain Multiplication using Dynamic Programming
void matrixChainOrder(const vector<int>& p) {
    int n = p.size(); // n - 1 matrices (A1 to An-1)

    // dp[i][j] stores the minimum scalar multiplications needed for A_i ... A_j
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // split[i][j] stores the index k that yields the optimal split point for A_i ... A_j
    vector<vector<int>> split(n, vector<int>(n, 0));

    // L is the chain length (number of matrices being multiplied together)
    for (int L = 2; L < n; ++L) {
        for (int i = 1; i < n - L + 1; ++i) {
            int j = i + L - 1;
            dp[i][j] = INT_MAX;

            // Try all possible split points k between i and j-1
            for (int k = i; k <= j - 1; ++k) {
                int cost = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];

                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    split[i][j] = k; // Store optimal split
                }
            }
        }
    }

    cout << "Minimum number of scalar multiplications: " << dp[1][n - 1] << "\n";
    cout << "Optimal Parenthesization: ";
    printParenthesization(1, n - 1, split);
    cout << "\n";
}

int main() {
    // Array p representing matrix dimensions
    // Dimensions: A1 = 10x30, A2 = 30x5, A3 = 5x60, A4 = 60x8
    vector<int> p = {10, 30, 5, 60, 8};

    matrixChainOrder(p);

    return 0;
}