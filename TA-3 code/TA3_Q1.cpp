#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000000;

void compute(int n, const vector<int> &isIn, vector<int> &dist)
{
    int last = -1;

    for (int i = 1; i <= n; ++i)
    {
        if (isIn[i]) last = i;
        if (last != -1) dist[i] = min(dist[i], i - last);
    }

    last = -1;
    for (int i = n; i >= 1; --i)
    {
        if (isIn[i]) last = i;
        if (last != -1) dist[i] = min(dist[i], last - i);
    }
}

int main()
{
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i)
    {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> comp(n + 1, -1);
    vector<vector<int>> components;
    int compCount = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (comp[i] != -1) continue;
        compCount++;
        vector<int> c;
        queue<int> q;
        q.push(i);
        comp[i] = compCount;
        while (!q.empty())
        {
            int u = q.front(); q.pop();
            c.push_back(u);
            for (int v : adj[u])
            {
                if (comp[v] == -1)
                {
                    comp[v] = compCount;
                    q.push(v);
                }
            }
        }
        components.push_back(c);
    }

    if (comp[1] == comp[n])
    {
        cout << 0 << '\n';
        return 0;
    }

    int idc1 = comp[1] - 1;
    int idcn = comp[n] - 1;

    vector<int> isC1(n + 1, 0), isCn(n + 1, 0);
    for (int v : components[idc1]) isC1[v] = 1;
    for (int v : components[idcn]) isCn[v] = 1;

    vector<int> dc1(n + 1, INF), dcn(n + 1, INF);
    for (int v : components[idc1]) dc1[v] = 0;
    for (int v : components[idcn]) dcn[v] = 0;
    compute(n, isC1, dc1);
    compute(n, isCn, dcn);

    int best = INF;
    for (int c = 0; c < compCount; ++c)
    {
        int min1 = INF, minn = INF;
        for (int v : components[c])
        {
            if (dc1[v] < INF)
            {
                int d = dc1[v];
                min1 = min(min1, d * d);
            }
            if (dcn[v] < INF)
            {
                int d = dcn[v];
                minn = min(minn, d * d);
            }
        }
        if (min1 < INF && minn < INF)
        {
            best = min(best, min1 + minn);
        }
    }

    cout << best << '\n';
    return 0;
}