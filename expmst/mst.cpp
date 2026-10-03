// name =abhishek 
//roll no.=25/DA/003
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// ==========================================
// 1. Disjoint Set Union (DSU) for Kruskal's
// ==========================================
class DSU {
    vector<int> parent, rank;
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    
    // Find with path compression
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]); 
    }
    
    // Union by rank
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            if (rank[root_i] < rank[root_j])
                parent[root_i] = root_j;
            else if (rank[root_i] > rank[root_j])
                parent[root_j] = root_i;
            else {
                parent[root_j] = root_i;
                rank[root_i]++;
            }
        }
    }
};

// ==========================================
// 2. Kruskal's Algorithm
// ==========================================
// Input: Vector of edges in format {weight, {u, v}}
void kruskalMST(int V, vector<pair<int, pair<int, int>>>& edges) {
    // Step 1: Sort edges by weight in ascending order
    sort(edges.begin(), edges.end()); 
    
    DSU dsu(V);
    int mst_weight = 0;

    cout << "--- Kruskal's MST Edges ---\n";
    for (auto& edge : edges) {
        int w = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;

        // Step 2: If u and v are in different sets, adding this edge doesn't form a cycle
        if (dsu.find(u) != dsu.find(v)) {
            dsu.unite(u, v);
            mst_weight += w;
            cout << "Edge: " << u << " - " << v << " \tWeight: " << w << "\n";
        }
    }
    cout << "Total Weight: " << mst_weight << "\n\n";
}

// ==========================================
// 3. Prim's Algorithm
// ==========================================
// Input: Adjacency list where adj[u] contains pairs of {neighbor, weight}
void primMST(int V, vector<vector<pair<int, int>>>& adj) {
    // Min-heap priority queue to store {weight, {u, v}}
    priority_queue<pair<int, pair<int, int>>, 
                   vector<pair<int, pair<int, int>>>, 
                   greater<pair<int, pair<int, int>>>> pq;
                   
    vector<bool> inMST(V, false);
    int mst_weight = 0;

    // Start from vertex 0 (using a dummy edge 0-0 with weight 0)
    pq.push({0, {0, 0}});

    cout << "--- Prim's MST Edges ---\n";
    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        int w = top.first;
        int u = top.second.first;
        int v = top.second.second;

        // If the destination vertex is already in the MST, skip it to avoid cycles
        if (inMST[v]) continue;

        inMST[v] = true;
        mst_weight += w;
        
        if (u != v) { // Skip printing the dummy starting edge
            cout << "Edge: " << u << " - " << v << " \tWeight: " << w << "\n";
        }

        // Add all adjacent edges of the newly added vertex to the priority queue
        for (auto& neighbor : adj[v]) {
            int next_v = neighbor.first;
            int edge_weight = neighbor.second;
            if (!inMST[next_v]) {
                pq.push({edge_weight, {v, next_v}});
            }
        }
    }
    cout << "Total Weight: " << mst_weight << "\n";
}

int main() {
    int V = 5;

    // Data for Kruskal's: Edge List formulation
    vector<pair<int, pair<int, int>>> edges = {
        {2, {0, 1}}, {6, {0, 3}}, {3, {1, 2}}, 
        {8, {1, 3}}, {5, {1, 4}}, {7, {2, 4}}
    };

    // Data for Prim's: Adjacency List formulation
    vector<vector<pair<int, int>>> adj(V);
    auto addEdge = [&](int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    };
    
    addEdge(0, 1, 2);
    addEdge(0, 3, 6);
    addEdge(1, 2, 3);
    addEdge(1, 3, 8);
    addEdge(1, 4, 5);
    addEdge(2, 4, 7);

    kruskalMST(V, edges);
    primMST(V, adj);

    return 0;
}