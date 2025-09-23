#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    int n, m;
    long long L;
    cin >> n >> m >> L;

    vector<vector<long long>> dist(n, vector<long long>(n, L));
    for (int i = 0; i < n; i++) dist[i][i] = 0;

    vector<tuple<int,int,int>> edges;
    for (int i = 0; i < m; i++) {
        int a, b, s;
        cin >> a >> b >> s;
        a--, b--;
        dist[a][b] = min(dist[a][b], (long long)s);
        dist[b][a] = min(dist[b][a], (long long)s);
        edges.push_back({a,b,s});
    }

    auto floyd = [&](vector<vector<long long>> d) {
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        return d;
    };

    auto baseDist = floyd(dist);

    long long baseCost = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            baseCost += baseDist[i][j];

    long long maxCost = baseCost;

    for (auto [a,b,s] : edges) {
        auto d = dist;
        d[a][b] = L;
        d[b][a] = L;

        auto newDist = floyd(d);

        long long newCost = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                newCost += newDist[i][j];

        maxCost = max(maxCost, newCost);
    }

    cout << baseCost << " " << maxCost << "\n";
    return 0;
}
