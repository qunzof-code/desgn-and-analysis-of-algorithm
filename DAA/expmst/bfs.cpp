#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

void bfs(unordered_map<char, vector<char>>& graph, char start_node) {
    unordered_set<char> visited;
    queue<char> q;

    // Initialize with the starting node
    q.push(start_node);
    visited.insert(start_node);

    cout << "BFS Traversal Order: ";

    while (!q.empty()) {
        // Dequeue the node at the front
        char current_node = q.front();
        q.pop();
        
        cout << current_node << " ";

        // Look at all neighbors of the current node
        for (char neighbor : graph[current_node]) {
            // If the neighbor hasn't been visited yet
            if (visited.find(neighbor) == visited.end()) {
                // Mark as visited and add to the back of the queue
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
    }
    cout << endl;
}

int main() {
    // Representing the same graph using an adjacency list
    unordered_map<char, vector<char>> graph = {
        {'A', {'B', 'C'}},
        {'B', {'A', 'D', 'E'}},
        {'C', {'A', 'F'}},
        {'D', {'B'}},
        {'E', {'B', 'F'}},
        {'F', {'C', 'E'}}
    };

    // Run BFS starting from node 'A'
    bfs(graph, 'A');
    
    return 0;
}