
#include <iostream>
#include <vector>
using namespace std;

vector<int> adj[100];
bool visited[100] = {};

void DFS(int v) {
    cout << v << " ";
    visited[v] = true;

    for (int u : adj[v])
        if (!visited[u])
            DFS(u);
}

int main() {
    int n, e, u, v, start;
    cout << "Enter vertices and edges: ";
    cin >> n >> e;

    cout << "Enter edges:\n";
    for (int i = 0; i < e; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cout << "Enter starting vertex: ";
    cin >> start;

    cout << "DFS Traversal: ";
    DFS(start);

    return 0;
}
