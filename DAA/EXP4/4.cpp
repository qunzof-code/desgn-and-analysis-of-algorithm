// ABHISHEK  25/DA/003
//EXP 4 DFS
#include <iostream>
#include <vector>
using namespace std;

void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited, vector<int>& component) {
    visited[node] = true;
    component.push_back(node);

    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adj, visited, component);
        }
    }
}

int main() {
    int n, e;
    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> e;

    vector<vector<int>> adj(n);

    cout << "Enter " << e << " edges (u v format, space-separated):\n";
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> visited(n, false);
    vector<vector<int>> components;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            vector<int> component;
            dfs(i, adj, visited, component);
            components.push_back(component);
        }
    }

    cout << "\nNumber of connected components: " << components.size() << endl;
    for (int i = 0; i < components.size(); i++) {
        cout << "Component " << i + 1 << ": ";
        for (int node : components[i]) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}