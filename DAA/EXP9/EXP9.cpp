// name= abhishek kumar
// roll no= 25/DA/003
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Type alias for pair to make the code cleaner. 
// First element is distance, second is vertex.
typedef pair<int, int> iPair;

// Function to find the shortest path from a given source vertex
void dijkstra(const vector<vector<pair<int, int>>>& adj, int V, int src) {
    // Priority queue to store vertices that are being preprocessed.
    // Use greater<iPair> to create a min-heap based on distance.
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;

    // Create a vector for distances and initialize all as infinite (INT_MAX)
    vector<int> dist(V, INT_MAX);

    // Insert source itself into priority queue and initialize its distance as 0
    pq.push(make_pair(0, src));
    dist[src] = 0;

    // Loop until the priority queue is empty
    while (!pq.empty()) {
        // The first vertex in pair is the minimum distance vertex
        // Extract it from priority queue
        int u = pq.top().second;
        int current_dist = pq.top().first;
        pq.pop();

        // Optional optimization: If we've already found a shorter path to u, skip
        if (current_dist > dist[u]) continue;

        // 'x' represents a neighboring vertex and its edge weight
        for (auto x : adj[u]) {
            int v = x.first;
            int weight = x.second;

            // If there is shorter path to v through u
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    // Print shortest distances stored in dist[]
    cout << "Vertex\tDistance from Source (Vertex " << src << ")\n";
    cout << "------------------------------------------\n";
    for (int i = 0; i < V; ++i) {
        if (dist[i] == INT_MAX) {
            cout << i << "\t\tINF\n";
        } else {
            cout << i << "\t\t" << dist[i] << "\n";
        }
    }
}

// Helper function to add an undirected edge to the adjacency list
void addEdge(vector<vector<pair<int, int>>>& adj, int u, int v, int weight) {
    adj[u].push_back(make_pair(v, weight));
    adj[v].push_back(make_pair(u, weight));
}

int main() {
    int V = 9; // Number of vertices in graph

    // Adjacency list representation of the graph
    // adj[u] stores a vector of pairs (v, weight)
    vector<vector<pair<int, int>>> adj(V);

    // Making the graph (Example based on a standard 9-node graph)
    addEdge(adj, 0, 1, 4);
    addEdge(adj, 0, 7, 8);
    addEdge(adj, 1, 2, 8);
    addEdge(adj, 1, 7, 11);
    addEdge(adj, 2, 3, 7);
    addEdge(adj, 2, 8, 2);
    addEdge(adj, 2, 5, 4);
    addEdge(adj, 3, 4, 9);
    addEdge(adj, 3, 5, 14);
    addEdge(adj, 4, 5, 10);
    addEdge(adj, 5, 6, 2);
    addEdge(adj, 6, 7, 1);
    addEdge(adj, 6, 8, 6);
    addEdge(adj, 7, 8, 7);

    // Run Dijkstra's algorithm starting from vertex 0
    dijkstra(adj, V, 0);

    return 0;
}