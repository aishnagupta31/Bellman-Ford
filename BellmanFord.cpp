#include <bits/stdc++.h>
using namespace std;

bool bellmanFord(int start, int V, vector<vector<pair<int, int>>> &adj, vector<int> &dist) {
    dist[start] = 0;

    // Relax all edges (V-1) times
    for (int i = 1; i <= V - 1; i++) {
        for (int u = 1; u <= V; u++) {
            for (auto edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
    }

    // Check for negative-weight cycles
    for (int u = 1; u <= V; u++) {
        for (auto edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                return false; // Negative-weight cycle detected
            }
        }
    }

    return true; // No negative-weight cycles
}

int main() {
    int vertices, edges;
    cin >> vertices >> edges;

    vector<vector<pair<int, int>>> adj(vertices + 1); // Adjacency list

    for (int i = 0; i < edges; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w}); // Directed graph with weights
    }

    int start;
    cout << "Enter start node: ";
    cin >> start;

    vector<int> dist(vertices + 1, INT_MAX); // Distance from start node

    if (bellmanFord(start, vertices, adj, dist)) {
        cout << "Shortest distances from node " << start << ":\n";
        for (int i = 1; i <= vertices; i++) {
            if (dist[i] == INT_MAX) {
                cout << "Node " << i << ": INF\n";
            } else {
                cout << "Node " << i << ": " << dist[i] << "\n";
            }
        }
    } else {
        cout << "Graph contains a negative-weight cycle.\n";
    }

    return 0;
}
