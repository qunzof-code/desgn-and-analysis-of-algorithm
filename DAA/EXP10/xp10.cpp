//naem abhishek  
// roll no. 25/DA/003
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Structure to represent a weighted directed edge
struct Edge {
    int u;      // Source vertex
    int v;      // Destination vertex
    int weight; // Edge weight
};

// Function to run Bellman-Ford SSSP and detect negative-weight cycles
void bellmanFord(int V, int src, const vector<Edge>& edges) {
    // Step 1: Initialize distances from source to all vertices as INFINITY
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    // Step 2: Relax all edges |V| - 1 times
    for (int i = 1; i <= V - 1; ++i) {
        bool updated = false; // Optimization: early stop if no distances change
        
        for (const auto& edge : edges) {
            int u = edge.u;
            int v = edge.v;
            int w = edge.weight;

            // Relaxation step with overflow guard
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                updated = true;
            }
        }

        // If no edge was relaxed during an entire pass, short-circuit
        if (!updated) break;
    }

    // Step 3: Check for negative-weight cycles using a V-th relaxation check
    bool hasNegativeCycle = false;
    for (const auto& edge : edges) {
        int u = edge.u;
        int v = edge.v;
        int w = edge.weight;

        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            hasNegativeCycle = true;
            break;
        }
    }

    // Output Result
    if (hasNegativeCycle) {
        cout << "Graph contains a negative-weight cycle reachable from source vertex " << src << "!\n";
        return;
    }

    cout << "Vertex\tDistance from Source (" << src << ")\n";
    cout << "--------------------------------\n";
    for (int i = 0; i < V; ++i) {
        if (dist[i] == INT_MAX) {
            cout << i << "\tINF\n";
        } else {
            cout << i << "\t" << dist[i] << "\n";
        }
    }
}

int main() {
    int V = 5; // Number of vertices
    
    // Weighted directed edges: {u, v, weight}
    vector<Edge> edges = {
        {0, 1, -1},
        {0, 2, 4},
        {1, 2, 3},
        {1, 3, 2},
        {1, 4, 2},
        {3, 2, 5},
        {3, 1, 1},
        {4, 3, -3} // Modify weight to -6 to introduce a negative cycle (1 -> 4 -> 3 -> 1)
    };

    int src = 0;
    bellmanFord(V, src, edges);

    return 0;
}