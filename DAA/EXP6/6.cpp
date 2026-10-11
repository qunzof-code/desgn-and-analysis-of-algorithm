// ABHISHEK   25/DA/003
//EXP 6 Write a program to solve the Fractional Knapsack problem using the Greedy approach.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int weight, value;
};

bool compare(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

int main() {
    int n;
    cout << "Enter number of items: ";
    cin >> n;

    vector<Item> items(n);
    cout << "Enter weight and value of each item:\n";
    for (int i = 0; i < n; i++) {
        cin >> items[i].weight >> items[i].value;
    }

    int capacity;
    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    sort(items.begin(), items.end(), compare);

    double totalValue = 0.0;
    int remaining = capacity;

    for (int i = 0; i < n; i++) {
        if (remaining <= 0) break;

        if (items[i].weight <= remaining) {
            totalValue += items[i].value;
            remaining -= items[i].weight;
        } else {
            double fraction = (double)remaining / items[i].weight;
            totalValue += items[i].value * fraction;
            remaining = 0;
        }
    }

    cout << "\nMaximum value in knapsack: " << totalValue << endl;

    return 0;
}