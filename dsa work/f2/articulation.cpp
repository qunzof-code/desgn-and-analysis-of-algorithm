//ABHISHEK 25/DA/003
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// DFS function to find Articulation Points
void DFS(int u, int parent, int& timer, const vector<vector<int>>& adj, 
         vector<int>& discovery_time, vector<int>& low, 
         vector<bool>& visited, vector<bool>& isCutVertex) {

    visited[u] = true;
    discovery_time[u] = low[u] = ++timer;
    int children = 0;

    for (int v : adj[u]) {
        if (v == parent) continue; // Skip edge to parent

        if (visited[v]) {
            // Back-edge found: update low value of u
            low[u] = min(low[u], discovery_time[v]);
        } else {
            // Forward-edge: visit child v
            children++;
            DFS(v, u, timer, adj, discovery_time, low, visited, isCutVertex);

            // Upon return, update low value of u
            low[u] = min(low[u], low[v]);

            // Condition 1 for non-root node
            if (parent != -1 && low[v] >= discovery_time[u]) {
                isCutVertex[u] = true;
            }
        }
    }

    // Condition 2 for root node
    if (parent == -1 && children > 1) {
        isCutVertex[u] = true;
    }
}

void findCutVertices(int V, const vector<vector<int>>& adj) {
    vector<int> discovery_time(V, -1);
    vector<int> low(V, -1);
    vector<bool> visited(V, false);
    vector<bool> isCutVertex(V, false);

    int timer = 0;

    // Run DFS from every unvisited node (handles disconnected graphs)
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            DFS(i, -1, timer, adj, discovery_time, low, visited, isCutVertex);
        }
    }

    cout << "Cut Vertices (Articulation Points) in the graph:\n";
    bool found = false;
    for (int i = 0; i < V; i++) {
        if (isCutVertex[i]) {
            cout << "Vertex " << i << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "None (Graph has no articulation points)\n";
    }
}

int main() {
    int V = 5; // Number of vertices (0 to 4)
    vector<vector<int>> adj(V);

    // Sample Graph Edges:
    // 1 --- 0 --- 2
    // |     |
    // 3 --- 4
    
    vector<pair<int, int>> edges = {
        {1, 0}, {0, 2}, {1, 3}, {3, 4}, {4, 1}
    };

    for (auto edge : edges) {
        adj[edge.first].push_back(edge.second);
        adj[edge.second].push_back(edge.first);
    }

    findCutVertices(V, adj);

    return 0;
}