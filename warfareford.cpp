#include <bits/stdc++.h>
using namespace std;


int bfs(int n, int s, int t, vector<vector<int>> &graph, vector<vector<int>> &capacity, vector<int> &parent)
{
    parent.clear();
    for(int i=0;i<n;i++)
    {
        parent.push_back(-1);
    }

    parent[s] = -2;

    queue<pair<int,int>> q;
    q.push({s,INT_MAX});

    while(!q.empty())
    {
        auto h = q.front();
        q.pop();

        int node = h.first;
        int flow = h.second;

        for(auto next:graph[node])
        {
            if(parent[next]==-1 and capacity[node][next])
            {
                parent[next] = node;
                int newf = min(flow, capacity[node][next]);

                if(next == t)
                return newf;

                q.push({next,newf});
            }
        }


    }

    return 0;
}


int ford_fulkerson(int n, int s, int t, vector<vector<int>> & graph, vector<vector<int>> &capacity)
{
    int flow=0;
    int newf=0;
    vector<int> parent;
    while(newf = bfs(n,s,t,graph,capacity,parent))
    {
        int now = t;
        flow += newf;
        while(now!=s)
        {
           
            int before = parent[now];
            capacity[before][now] -= newf;
            capacity[now][before] += newf;
            now = before;
        }
    }

    return flow;
}



int main()
{
    int n=0, m=0, s=0, t=0;
    cin >> n >> m >> s >> t;
    int mine = INT_MAX;

    vector<vector<int>> edges;
    vector<vector<int>> graph(n,vector<int>());
    vector<vector<int>> capacity(n,vector<int>(n,0)), duplac;


    int maxe = 0;

    for(int i=0;i<m;i++)
    {
        int a=0,b=0,weight=0;
        cin >> a >> b >> weight;

        capacity[a][b] = weight;
        graph[a].push_back(b);
        graph[b].push_back(a);
        edges.push_back({a,b,weight});
    }

    pair<int,int> edge_remove = {0,0};

    for(auto edge:edges)
    {
        duplac = capacity;
        int a = edge[0];
        int b = edge[1];
        int thisc = duplac[a][b];

        duplac[a][b] = 0;

        auto it = find(graph[a].begin(), graph[a].end(), b);
        if (it != graph[a].end())
        {
            graph[a].erase(it);
        }

        it = find(graph[b].begin(), graph[b].end(), a);
        if (it != graph[b].end())
        {
            graph[b].erase(it);
        }

        int rez = ford_fulkerson(n,s,t,graph,duplac);
        if ( rez < mine)
        {
            edge_remove.first = edge[0];
            edge_remove.second = edge[1];
            mine = rez;
        }
       
        graph[a].push_back(b);
        graph[b].push_back(a);
        duplac[a][b] = thisc;
    }
   
    cout << mine << endl;
    cout << edge_remove.first << ' ' << edge_remove.second;

    return 0;
}