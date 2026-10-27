//25/DA/003
//ABHISHEK
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Recursive helper function to place queens row by row using backtracking
void solveNQueensHelper(int row, int n, vector<string>& board, 
                        vector<bool>& cols, vector<bool>& diag1, vector<bool>& diag2, 
                        vector<vector<string>>& solutions) {
    // Base Case: All N queens have been placed successfully
    if (row == n) {
        solutions.push_back(board);
        return;
    }

    for (int col = 0; col < n; ++col) {
        int d1 = row - col + n - 1; // Index for main diagonal (\)
        int d2 = row + col;         // Index for anti-diagonal (/)

        // Safety Check: Skip if column or diagonals are already threatened
        if (cols[col] || diag1[d1] || diag2[d2]) continue;

        // Place Queen (Make Choice)
        board[row][col] = 'Q';
        cols[col] = diag1[d1] = diag2[d2] = true;

        // Recurse to place the queen in the next row
        solveNQueensHelper(row + 1, n, board, cols, diag1, diag2, solutions);

        // Backtrack: Remove Queen (Undo Choice)
        board[row][col] = '.';
        cols[col] = diag1[d1] = diag2[d2] = false;
    }
}

// Function to initiate N-Queens solver and print configurations
void solveNQueens(int n) {
    vector<vector<string>> solutions;
    vector<string> board(n, string(n, '.'));

    // Hash vectors for O(1) collision checks
    vector<bool> cols(n, false);
    vector<bool> diag1(2 * n - 1, false); // Main diagonals: row - col + n - 1
    vector<bool> diag2(2 * n - 1, false); // Anti-diagonals: row + col

    solveNQueensHelper(0, n, board, cols, diag1, diag2, solutions);

    cout << "Total distinct solutions for " << n << "-Queens: " << solutions.size() << "\n\n";

    // Print all generated board configurations
    for (size_t k = 0; k < solutions.size(); ++k) {
        cout << "Solution " << k + 1 << ":\n";
        for (const string& row : solutions[k]) {
            for (char cell : row) {
                cout << cell << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
}

int main() {
    int n = 4; // Board size (N x N)
    solveNQueens(n);

    return 0;
}