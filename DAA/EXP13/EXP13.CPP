//25/DA/003
//ABHISHEK 
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Function to compute and print the Longest Common Subsequence (LCS)
void findLCS(const string& s1, const string& s2) {
    int m = s1.length();
    int n = s2.length();

    // dp[i][j] stores the length of LCS of s1[0...i-1] and s2[0...j-1]
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Step 1: Build the DP table bottom-up
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1]; // Characters match
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]); // Skip a character from s1 or s2
            }
        }
    }

    // Length of the longest common subsequence
    int lcsLength = dp[m][n];

    // Step 2: Backtrack from dp[m][n] to reconstruct the actual LCS string
    string lcsStr = "";
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            lcsStr.push_back(s1[i - 1]); // Match found; include character
            --i;
            --j;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            --i; // Move up
        } else {
            --j; // Move left
        }
    }

    // Since character collection was reverse (from end to start), reverse the result
    reverse(lcsStr.begin(), lcsStr.end());

    cout << "Length of LCS: " << lcsLength << "\n";
    cout << "LCS String: " << lcsStr << "\n";
}

int main() {
    string s1 = "AGGTAB";
    string s2 = "GXTXAYB";

    findLCS(s1, s2);

    return 0;
}