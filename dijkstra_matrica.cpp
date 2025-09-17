#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int main() {
    int V; 
    cout << "Vnesi broj na teminja"<<endl;
    cin >> V;

    vector<vector<int>> graph(V, vector<int>(V));
    cout << "Vnesi ja matricata"<<endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) { /*prave gu matricata*/
            cin >> graph[i][j];
            if (graph[i][j] == 0 && i != j) {
                graph[i][j] = numeric_limits<int>::max(); /*ako e 0, znaci nema rebro i ga zamenuva so infinity*/
            }
        }
    }

    int matej;
    cout << "Od koe teme sakas da najdes najkratok pat? "<<endl;
    cin >> matej;

    vector<int> dist(V, numeric_limits<int>::max());  /* u dist ga cuva najmalata distanca od matej, prvicno site sa infinity, 
    a distancata na matej e 0 poso od pocetoko sekat e 0*/
    vector<bool> visited(V, false); /*visited gi cuva do koi nodovi e najdena najkratkata distanca*/
    dist[matej] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = -1;
        for (int i = 0; i < V; i++) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u])) { /*naoga gi neposetenite teminja so najmala distanca*/
                u = i;
            }
        }

        visited[u] = true; /* znaemo gu najmalata distanca do toa teme*/

        for (int v = 0; v < V; v++) {                                       /*For each neighbor v of u*/
            if (graph[u][v] != numeric_limits<int>::max() && !visited[v]) { /*If there is an edge (graph[u][v] != ∞) and v is not visited*/
                if (dist[u] + graph[u][v] < dist[v]) {                      /*Check if going through u gives a shorter path to v*/
                    dist[v] = dist[u] + graph[u][v];                        /*If yes, update dist[v]*/
                }
            }
        }
    }

    cout << endl << "najkratkite rastojanija od temeto " << matej << " se:" << endl;
    for (int i = 0; i < V; i++) {
        cout << endl << "do " << i << ": ";
        if (dist[i] == numeric_limits<int>::max()) {
            cout << "INF" << endl;
        } else {
            cout << dist[i] << endl;
        }
    }

    return 0;
}
