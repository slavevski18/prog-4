#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int v, rev;
    long long cap;
};

struct PushRelabel {
    int n;
    vector<vector<Edge>> G;
    vector<long long> excess;
    vector<int> height;
    vector<int> count;
    queue<int> Q;

    PushRelabel(int nodes) {
        n = nodes;
        G = vector<vector<Edge>>(n);
        excess = vector<long long>(n, 0);
        height = vector<int>(n, 0);
        count = vector<int>(2 * n, 0);
    }

    void addEdge(int u, int v, long long cap) {
        Edge a{v, (int)G[v].size(), cap};
        Edge b{u, (int)G[u].size(), 0};
        G[u].push_back(a);
        G[v].push_back(b);
    }

    void push(int u, Edge &e) {
        long long flow = min(excess[u], e.cap);
        if (height[u] == height[e.v] + 1 && flow > 0) {
            e.cap -= flow;
            G[e.v][e.rev].cap += flow;
            excess[u] -= flow;
            excess[e.v] += flow;
            if (excess[e.v] == flow && e.v != 0 && e.v != n - 1) {
                Q.push(e.v);
            }
        }
    }

    void relabel(int u) {
        int h = INT_MAX;
        for (int i = 0; i < (int)G[u].size(); i++) {
            if (G[u][i].cap > 0) {
                h = min(h, height[G[u][i].v]);
            }
        }
        if (h < INT_MAX) {
            height[u] = h + 1;
        }
    }

    void discharge(int u) {
        for (int i = 0; i < (int)G[u].size() && excess[u] > 0; i++) {
            push(u, G[u][i]);
        }
        if (excess[u] > 0) {
            relabel(u);
        }
    }

    long long maxFlow(int s, int t) {
        height[s] = n;
        if ((int)count.size() >= n + 1) {
            count[0] = n - 1;
            count[n] = 1;
        }

        // initialize preflow from source
        for (int i = 0; i < (int)G[s].size(); i++) {
            long long c = G[s][i].cap;
            if (c > 0) {
                excess[s] += c;
                push(s, G[s][i]);
            }
        }

        while (!Q.empty()) {
            int u = Q.front(); Q.pop();
            if (u == s || u == t) continue;
            discharge(u);
            if (excess[u] > 0) Q.push(u);
        }
        return excess[t];
    }
};

int main() {
    srand((unsigned)time(0));
    int n = rand() % 49 + 2;  // between 2 and 50
    PushRelabel pr(n);

    // Random edges
    int edges = rand() % (n * n / 2) + n;
    for (int i = 0; i < edges; i++) {
        int u = rand() % n;
        int v = rand() % n;
        if (u != v) {
            long long cap = rand() % 20 + 1;
            pr.addEdge(u, v, cap);
        }
    }

    int s = 0;
    int t = n - 1;

    cout << "Nodes: " << n << "\n";
    cout << "Edges: " << edges << "\n";

    long long flow = pr.maxFlow(s, t);
    cout << "Max Flow from " << s << " to " << t << " = " << flow << "\n";
    return 0;
}