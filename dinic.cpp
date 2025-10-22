#include <bits/stdc++.h>
using namespace std;

struct Connection
{
    int start, end;
    long long capacity, current = 0;

    Connection(int from, int to, long long cap)
    {
        start = from;
        end = to;
        capacity = cap;
    }
};

struct MaxFlow
{
    long long INF = 1e18;
    vector<Connection> links;
    vector<vector<int>> network;

    int nodes, edgeCount = 0;
    int source, sink;

    vector<int> depth, edgePtr;
    queue<int> que;

    MaxFlow(int totalNodes, int sNode, int tNode)
    {
        nodes = totalNodes;
        source = sNode;
        sink = tNode;

        network.resize(nodes);
        depth.resize(nodes);
        edgePtr.resize(nodes);
    }

    void addConnection(int from, int to, long long cap)
    {
        links.push_back(Connection(from, to, cap));
        links.push_back(Connection(to, from, 0));

        network[from].push_back(edgeCount);
        network[to].push_back(edgeCount + 1);

        edgeCount += 2;
    }

    bool buildLevelGraph()
    {
        while (!que.empty())
        {
            int cur = que.front();
            que.pop();

            for (int i = 0; i < (int)network[cur].size(); i++)
            {
                int id = network[cur][i];
                if (links[id].capacity == links[id].current)
                    continue;

                if (depth[links[id].end] != -1)
                    continue;

                depth[links[id].end] = depth[cur] + 1;
                que.push(links[id].end);
            }
        }

        return depth[sink] != -1;
    }

    long long sendFlow(int node, long long pushed)
    {
        if (pushed == 0)
            return 0;

        if (node == sink)
            return pushed;

        for (int &cid = edgePtr[node]; cid < (int)network[node].size(); cid++)
        {
            int id = network[node][cid];
            int next = links[id].end;

            if (depth[node] + 1 != depth[next])
                continue;

            long long flowSent = sendFlow(next, min(pushed, links[id].capacity - links[id].current));
            if (flowSent == 0)
                continue;

            links[id].current += flowSent;
            links[id ^ 1].current -= flowSent;

            return flowSent;
        }

        return 0;
    }

    long long calculateMaxFlow()
    {
        long long totalFlow = 0;

        while (true)
        {
            fill(depth.begin(), depth.end(), -1);
            depth[source] = 0;

            while (!que.empty())
                que.pop();
            que.push(source);

            if (!buildLevelGraph())
                break;

            fill(edgePtr.begin(), edgePtr.end(), 0);

            while (true)
            {
                long long pushedFlow = sendFlow(source, INF);
                if (pushedFlow == 0)
                    break;
                totalFlow += pushedFlow;
            }
        }

        return totalFlow;
    }
};

int main()
{
    int vertices = 0, edges = 0, src = 0, snk = 0;
    cin >> vertices >> edges >> src >> snk;

    MaxFlow solver(vertices, src, snk);

    for (int i = 0; i < edges; i++)
    {
        int from, to;
        long long cap;
        cin >> from >> to >> cap;
        solver.addConnection(from, to, cap);
    }

    long long answer = solver.calculateMaxFlow();
    cout << answer;

    return 0;
}
