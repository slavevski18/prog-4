#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int rev;      
    int cap;      
    int orig_cap; 
};

struct OrigEdgeInfo {
    int u, v;
    int orig_cap;
    int flow;
};

int MAX_PRINT_PATHS = 1000; 
vector<vector<Edge>> graph_flow;
vector<OrigEdgeInfo> original_edges;

void add_edge(int u, int v, int c) {
    Edge a;
    a.to = v;
    a.rev = (int)graph_flow[v].size();
    a.cap = c;
    a.orig_cap = c;

    Edge b;
    b.to = u;
    b.rev = (int)graph_flow[u].size();
    b.cap = 0;
    b.orig_cap = 0;

    graph_flow[u].push_back(a);
    graph_flow[v].push_back(b);

    OrigEdgeInfo info;
    info.u = u;
    info.v = v;
    info.orig_cap = c;
    info.flow = 0;
    original_edges.push_back(info);
}

vector<int> tmp_path;
vector<vector<int>> all_paths;
int path_count_limit = 1000;

void dfs_list_paths(int u, int t, vector<int>& visited) {
    if ((int)all_paths.size() >= path_count_limit) return;
    if (u == t) {
        all_paths.push_back(tmp_path);
        return;
    }

    visited[u] = 1;
    for (int ei = 0; ei < (int)graph_flow[u].size(); ei++) {
        Edge &e = graph_flow[u][ei];
        if (e.orig_cap > 0 && !visited[e.to]) {
            tmp_path.push_back(e.to);
            dfs_list_paths(e.to, t, visited);
            tmp_path.pop_back();

            if ((int)all_paths.size() >= path_count_limit) {
                visited[u] = 0;
                return;
            }
        }
    }
    visited[u] = 0;
}

int bfs_find_path(int s, int t, vector<pair<int,int>>& parent) {
    int n = (int)graph_flow.size();
    parent.assign(n, make_pair(-1, -1));

    queue<int> q;
    q.push(s);
    parent[s] = make_pair(-2, -1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int ei = 0; ei < (int)graph_flow[u].size(); ei++) {
            Edge &e = graph_flow[u][ei];
            if (e.cap > 0 && parent[e.to].first == -1) {
                parent[e.to] = make_pair(u, ei);
                if (e.to == t) return 1;
                q.push(e.to);
            }
        }
    }
    return 0;
}

int main() {
    
    

    int n, m;
    if (!(cin >> n >> m)) {
        cerr << "Invalid input.\n";
        return 0;
    }

    graph_flow.assign(n, vector<Edge>());
    original_edges.clear();

    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        add_edge(u, v, c);
    }

    int s, t;
    cin >> s >> t;

    cout << "\n--- Simple s->t paths (original graph) ---\n";
    all_paths.clear();
    tmp_path.clear();
    tmp_path.push_back(s);
    vector<int> visited(n, 0);
    path_count_limit = MAX_PRINT_PATHS;
    dfs_list_paths(s, t, visited);

    if (all_paths.empty()) {
        cout << "No simple path from " << s << " to " << t << ".\n";
    } else {
        cout << "Found " << all_paths.size() << " path(s):\n";
        for (int i = 0; i < (int)all_paths.size(); i++) {
            cout << "Path " << i + 1 << ": ";
            for (int j = 0; j < (int)all_paths[i].size(); j++) {
                if (j > 0) cout << " -> ";
                cout << all_paths[i][j];
            }
            cout << "\n";
        }
    }

    int max_flow = 0;
    vector<pair<int,int>> parent;
    int step = 0;

    auto compute_and_print_orig_edges = [&](int step_num) {
        for (int i = 0; i < (int)original_edges.size(); i++) {
            OrigEdgeInfo &oe = original_edges[i];
            oe.flow = 0;

            int u = oe.u;
            int v = oe.v;
            for (int j = 0; j < (int)graph_flow[u].size(); j++) {
                Edge &e = graph_flow[u][j];
                if (e.to == v && e.orig_cap == oe.orig_cap) {
                    oe.flow = oe.orig_cap - e.cap;
                    break;
                }
            }
        }

        cout << "State of edges after step " << step_num << ":\n";
        cout << "u -> v   orig_cap   flow   residual_forward\n";
        for (int i = 0; i < (int)original_edges.size(); i++) {
            OrigEdgeInfo &oe = original_edges[i];
            int residual_forward = oe.orig_cap - oe.flow;
            cout << oe.u << " -> " << oe.v << "     " << oe.orig_cap
                 << "         " << oe.flow
                 << "         " << residual_forward << "\n";
        }
        cout << "-----------------------------------------\n";
    };

    while (bfs_find_path(s, t, parent)) {
        vector<int> path_nodes;
        int cur = t;
        int bottleneck = INT_MAX;

        while (parent[cur].first != -2) {
            int prev = parent[cur].first;
            int ei = parent[cur].second;
            Edge &e = graph_flow[prev][ei];
            if (e.cap < bottleneck) bottleneck = e.cap;
            path_nodes.push_back(prev);
            cur = prev;
        }
        path_nodes.push_back(t);
        reverse(path_nodes.begin(), path_nodes.end());

        step++;
        cout << "Step " << step << ": Augmenting path: ";
        for (int i = 0; i < (int)path_nodes.size(); i++) {
            if (i > 0) cout << " -> ";
            cout << path_nodes[i];
        }
        cout<<endl << bottleneck << "\n";

        cur = t;
        while (parent[cur].first != -2) {
            int prev = parent[cur].first;
            int ei = parent[cur].second;
            Edge &e = graph_flow[prev][ei];
            Edge &rev = graph_flow[e.to][e.rev];
            e.cap -= bottleneck;
            rev.cap += bottleneck;
            cur = prev;
        }

        max_flow += bottleneck;
        cout << "Total flow now = " << max_flow << "\n";

        compute_and_print_orig_edges(step);
    }

    cout << "\nNo more augmenting paths. Maximum flow = " << max_flow << "\n";
    return 0;
}
