#include <iostream>
#include <vector>
using namespace std;

int main() {
    int V, E; 
    cin >> V >> E;

    vector<vector<int>> adj(V);

    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); 
    }

    for (int i = 0; i < V; i++) {
        cout << i << ": ";
        if (adj[i].empty()) {
            cout << "*empty*";
        } else {
            for (int neighbor : adj[i]) {
                cout << neighbor << " ";
            }
        }
        cout << "\n";
    }

    return 0;
}
