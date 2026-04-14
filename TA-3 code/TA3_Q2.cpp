#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n, m; cin >> n >> m;
    vector<vector<pair<int,int>>> adj(n + 1);
    vector<pair<int, int>> edges;
    vector<bool> used(m, false);
    vector<int> degree(n + 1, 0);
    for (int i = 0; i < m; ++i)
    {
        int u, v; cin >> u >> v;
        edges.push_back({u, v});
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
        degree[u]++; degree[v]++;
    }
    int oddcount = 0, start;
    for(int i = 1; i <= n; ++i)
    {
        if(degree[i] % 2 != 0)
        {
            oddcount++;
            start = i;
        }
    }
    if(oddcount != 2) {
        cout << "-1" << endl;
        return 0;
    }
    vector<bool> visited(n + 1, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while(!q.empty())
    {
        int node = q.front(); q.pop();
        for(auto &neighbor : adj[node])
        {
            int v = neighbor.first;
            if(!visited[v])
            {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    for(int i = 1; i <= n; ++i)
    {
        if(degree[i] > 0 && !visited[i])
        {
            cout << "-1" << endl;
            return 0;
        }
    }
    vector<int> path;
    stack<int> st;
    st.push(start);
    while(!st.empty())
    {
        int node = st.top();
        bool found = false;

        while(!adj[node].empty())
        {
            auto [v, edge_index] = adj[node].back();
            adj[node].pop_back();
            if(!used[edge_index])
            {
                used[edge_index] = true;
                st.push(v);
                found = true;
                break;
            }
        }
        if(!found)
        {
            path.push_back(node);
            st.pop();
        }
    }
    for(int i = 0; i < path.size(); ++i)
    {
        cout << path[i] << " ";
    }
}