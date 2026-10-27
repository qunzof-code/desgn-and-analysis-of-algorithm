//25/DA/003
//ABHISHEK 
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to solve the 0/1 Knapsack Problem using Dynamic Programming
void knapsack(int capacity, const vector<int>& weights, const vector<int>& values) {
    int n = weights.size();

    // dp[i][w] stores the max value using a subset of the first i items with capacity limit w
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    // Step 1: Build the DP table bottom-up
    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= capacity; ++w) {
            // Check if current item's weight can fit into current capacity w
            if (weights[i - 1] <= w) {
                // Include item or exclude item (take maximum)
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            } else {
                // Cannot include current item; carry forward previous optimal value
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int maxValue = dp[n][capacity];

    // Step 2: Backtrack to find which items were selected
    vector<int> selectedItems;
    int w = capacity;
    for (int i = n; i > 0 && maxValue > 0; --i) {
        // If the value came from dp[i-1][w], the item was NOT included
        if (dp[i][w] != dp[i - 1][w]) {
            selectedItems.push_back(i - 1); // Store 0-based index of item
            w -= weights[i - 1];            // Deduct weight
        }
    }

    // Output Result
    cout << "Maximum value in Knapsack = " << maxValue << "\n";
    cout << "Selected items (0-indexed): ";
    for (int i = selectedItems.size() - 1; i >= 0; --i) {
        cout << selectedItems[i] << " (wt: " << weights[selectedItems[i]] 
             << ", val: " << values[selectedItems[i]] << ") ";
    }
    cout << "\n";
}

int main() {
    vector<int> values = {60, 100, 120};
    vector<int> weights = {10, 20, 30};
    int capacity = 50;

    knapsack(capacity, weights, values);

    return 0;
}