#include <iostream>
#include <vector>
using namespace std;

int main() {
    int V; 
    cout << "Vnesi broj na teminja" << endl;
    cin >> V;

    const int INF = 1000000; 

    vector<vector<int>> graph(V, vector<int>(V));
    cout << "Vnesi ja matricata" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cin >> graph[i][j];
            if (graph[i][j] == 0 && i != j) {
                graph[i][j] = INF; 
            }
        }
    }

    int matej;
    cout << "Od koe teme sakas da najdes najkratok pat? " << endl;
    cin >> matej;

    vector<int> dist(V, INF);
    vector<bool> visited(V, false);
    dist[matej] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = -1;
        for (int i = 0; i < V; i++) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }

        visited[u] = true;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] != INF && !visited[v]) {
                if (dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }
    }

    cout << endl << "najkratkite rastojanija od temeto " << matej << " se:" << endl;
    for (int i = 0; i < V; i++) {
        cout << endl << "do " << i << ": ";
        if (dist[i] == INF) {
            cout << "INF" << endl;
        } else {
            cout << dist[i] << endl;
        }
    }

    return 0;
}

