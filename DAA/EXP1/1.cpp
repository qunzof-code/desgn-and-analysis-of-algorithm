// ABHISHEK  25/DA/0003
// Exp 1 Merge sort using recursive and Iterative method
#include <iostream>
#include <vector>
#include <algorithm> // Required for min()

using namespace std;

void merG(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) temp.push_back(arr[i++]);
        else temp.push_back(arr[j++]);
    }
    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);

    for (int k = left; k <= right; k++)
        arr[k] = temp[k - left];
}

void mergeSortRecursive(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSortRecursive(arr, left, mid);
    mergeSortRecursive(arr, mid + 1, right);
    merG(arr, left, mid, right); // FIXED: Changed merge to merG
}

void mergeSortIterative(vector<int>& arr) {
    int n = arr.size();
    for (int width = 1; width < n; width *= 2) {
        for (int left = 0; left < n - width; left += 2 * width) {
            int mid = left + width - 1;
            int right = min(left + 2 * width - 1, n - 1);
            merG(arr, left, mid, right); // FIXED: Changed merge to merG
        }
    }
}

void printArr(const vector<int>& arr) {
    for (int x : arr) cout << x << " ";
    cout << "\n";
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> a(n);
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> b = a;

    mergeSortRecursive(a, 0, a.size() - 1);
    cout << "Recursive: "; printArr(a);

    mergeSortIterative(b);
    cout << "Iterative: "; printArr(b);

    return 0;
}