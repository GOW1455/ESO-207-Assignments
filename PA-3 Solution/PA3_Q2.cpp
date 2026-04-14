#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main()
{
    int n, m; cin >> n >> m;

    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    
    vector<int> parent(n+1), depth(n+1), tin(n+1), tout(n+1), visited(n+1);
    int timer = 0;

    stack<pair<int,int>> s;
    s.push({1, 0});
    while (!s.empty())
    {
        auto[v, p] = s.top();
        if (!visited[v]) 
        {
            visited[v] = true;
            parent[v] = p;
            tin[v] = ++timer;
            for (int to : g[v])
            {
                if (!visited[to])
                {
                    depth[to] = depth[v] + 1;
                    s.push({to, v});
                }
            }
        }
        else
        {
            tout[v] = ++timer;
            s.pop();
        }
    }

    auto isAncestor = [&](int a, int b) {
        return tin[a] <= tin[b] && tout[b] <= tout[a];
    };

    while(m--)
    {
        int k; cin >> k;
        vector<int> nodes(k);
        for (int i = 0; i < k; i++) cin >> nodes[i];
        for(int i = 0; i < k; i++)
        {
            if(nodes[i]!=1) nodes[i] = parent[nodes[i]];
        }

        int deepest = nodes[0];
        for(auto v: nodes)
        {
            if(depth[v] > depth[deepest]) deepest = v;
        }
        
        bool ok = true;
        for (int v : nodes) {
            if (!isAncestor(v, deepest)) {
                ok = false;
                break;
            }
        }
        cout << (ok ? "YES" : "NO");
        cout << endl;
    }
}