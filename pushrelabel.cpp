// push_relabel_correct.cpp
// Usage: provide input as:
// n m
// u v capacity    (m lines, 0-based node indices)
// ...
// s t
//
// Example:
// 4 5
// 0 1 100
// 0 2 100
// 1 2 1
// 1 3 100
// 2 3 100
// 0 3

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int rev;           // index of reverse edge in adjacency list of `to`
    long long cap;
    Edge(int _to=0, int _rev=0, long long _cap=0) : to(_to), rev(_rev), cap(_cap) {}
};

struct PushRelabel {
    int n;
    vector<vector<Edge>> G;
    vector<long long> excess;
    vector<int> height;
    vector<int> cntHeight;
    vector<int> cur;            // current edge pointer for each vertex
    queue<int> activeQ;
    vector<char> inQueue;

    PushRelabel(int nodes=0) { init(nodes); }

    void init(int nodes) {
        n = nodes;
        G.assign(n, {});
        excess.assign(n, 0);
        height.assign(n, 0);
        cntHeight.assign(2*n + 5, 0);
        cur.assign(n, 0);
        while(!activeQ.empty()) activeQ.pop();
        inQueue.assign(n, 0);
    }

    void addEdge(int u, int v, long long cap) {
        Edge a(v, (int)G[v].size(), cap);
        Edge b(u, (int)G[u].size(), 0);
        G[u].push_back(a);
        G[v].push_back(b);
    }

    // push from u through edge index ei
    void pushEdge(int u, int ei) {
        Edge &e = G[u][ei];
        if (e.cap == 0) return;
        int v = e.to;
        long long send = min(excess[u], e.cap);
        if (send == 0) return;
        e.cap -= send;
        G[v][e.rev].cap += send;
        excess[u] -= send;
        bool activate = (excess[v] == 0 && send > 0);
        excess[v] += send;
        if (activate && v != 0 && v != n-1) enqueue(v);
    }

    void enqueue(int v) {
        if (!inQueue[v]) {
            activeQ.push(v);
            inQueue[v] = 1;
        }
    }

    // gap heuristic: all vertices with height > g become at least n+1 (disconnected)
    void gap(int g) {
        for (int v = 0; v < n; ++v) {
            if (height[v] > g && height[v] < n+1) {
                cntHeight[height[v]]--;
                height[v] = n + 1;
                cntHeight[height[v]]++;
                cur[v] = 0;
            }
        }
    }

    void relabel(int u) {
        int minh = INT_MAX;
        for (const Edge &e : G[u]) {
            if (e.cap > 0) minh = min(minh, height[e.to]);
        }
        if (minh < INT_MAX) {
            int oldh = height[u];
            cntHeight[oldh]--;
            height[u] = minh + 1;
            cntHeight[height[u]]++;
            cur[u] = 0;
            // gap heuristic trigger
            if (cntHeight[oldh] == 0) gap(oldh);
        }
    }

    void discharge(int u, int s, int t) {
        while (excess[u] > 0) {
            if (cur[u] >= (int)G[u].size()) {
                relabel(u);
                if (height[u] > n) break; // disconnected by gap
                continue;
            }
            Edge &e = G[u][cur[u]];
            if (e.cap > 0 && height[u] == height[e.to] + 1) {
                pushEdge(u, cur[u]);
            } else {
                cur[u]++;
            }
        }
    }

    long long maxFlow(int s, int t) {
        // initialize
        for (int i = 0; i < n; ++i) {
            height[i] = 0;
            excess[i] = 0;
            cur[i] = 0;
            inQueue[i] = 0;
        }
        fill(cntHeight.begin(), cntHeight.end(), 0);

        height[s] = n;
        cntHeight[0] = n - 1;
        cntHeight[n] = 1;

        // preflow from source
        for (int i = 0; i < (int)G[s].size(); ++i) {
            long long c = G[s][i].cap;
            if (c > 0) {
                int v = G[s][i].to;
                G[s][i].cap -= c;
                G[v][G[s][i].rev].cap += c;
                excess[s] -= c; // will be negative, but we don't use excess[s] afterwards
                bool activate = (excess[v] == 0 && c > 0);
                excess[v] += c;
                if (activate && v != s && v != t) enqueue(v);
            }
        }

        // process active vertices
        while (!activeQ.empty()) {
            int u = activeQ.front(); activeQ.pop();
            inQueue[u] = 0;
            if (u == s || u == t) continue;
            discharge(u, s, t);
            if (excess[u] > 0) enqueue(u);
        }

        return excess[t];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) {
        cerr << "Input error: expected n m\n";
        return 1;
    }
    PushRelabel pr;
    pr.init(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        long long cap;
        cin >> u >> v >> cap;
        if (u < 0 || u >= n || v < 0 || v >= n) {
            cerr << "Edge node index out of range\n";
            return 1;
        }
        pr.addEdge(u, v, cap);
    }

    int s, t;
    cin >> s >> t;
    if (s < 0 || s >= n || t < 0 || t >= n) {
        cerr << "Source/sink out of range\n";
        return 1;
    }

    long long flow = pr.maxFlow(s, t);
    cout << "Nodes: " << n << "\n";
    cout << "Edges: " << m << "\n";
    cout << "Source: " << s << " Sink: " << t << "\n";
    cout << "MaxFlow: " << flow << "\n";
    return 0;
}
