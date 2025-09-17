#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

struct Edge {
    int u, v, w; 
};

int main() {
    int V = 50;   
    int E = 200;  

    vector<Edge> edges;

    srand(time(0));

    for (int i = 0; i < E; i++) {
        int u = rand() % V;         
        int v = rand() % V;            
        while (v == u) v = rand() % V; 

        int w = (rand() % 50) + 1;     

        edges.push_back({u, v, w});    
    }

    int matej = 0;   
    const int INF = 1000000000; 
    vector<int> dist(V, INF);  
    dist[matej] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (auto &edge : edges) {
            if (dist[edge.u] != INF && dist[edge.u] + edge.w < dist[edge.v]) {  
                dist[edge.v] = dist[edge.u] + edge.w;                          
            }
        }
    }

    cout << "Najmalo rastojanie od " << matej << ":" << endl;
    for (int i = 0; i < V; i++) {
        cout << "Do " << i << " e ";
        if (dist[i] == INF) {
            cout << "INF";
        }
        else
            cout << dist[i];
        cout << endl;
    }

    return 0;
}
