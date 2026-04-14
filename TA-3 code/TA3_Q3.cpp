#include<bits/stdc++.h>
using namespace std;

int minTramsToReach(vector<vector<int>>& routes, int source, int target) {
    int n = routes.size();
    if (source == target) return 0;

    unordered_map<int, vector<int>> islandToRoutes;
    for (int i = 0; i < n; i++) {
        for (int island : routes[i]) {
            islandToRoutes[island].push_back(i);
        }
    }

    vector<vector<int>> adj(n);
    for (auto& [island, rlist] : islandToRoutes) {
        for (int i = 0; i < (int)rlist.size(); i++) {
            for (int j = i + 1; j < (int)rlist.size(); j++) {
                adj[rlist[i]].push_back(rlist[j]);
                adj[rlist[j]].push_back(rlist[i]);
            }
        }
    }

    queue<pair<int,int>> q;
    vector<int> visited(n, 0);

    for (int r : islandToRoutes[source]) {
        q.push({r, 1});
        visited[r] = 1;
    }

    // BFS traversal
    while (!q.empty()) {
        auto [routeIdx, trams] = q.front();
        q.pop();

        for (int island : routes[routeIdx]) {
            if (island == target) return trams;
        }
        for (int nbr : adj[routeIdx]) {
            if (!visited[nbr]) {
                visited[nbr] = 1;
                q.push({nbr, trams + 1});
            }
        }
    }

    return -1;
}

int main()
{
    int n, m, source, target;
    cin >> n >> m >> source >> target;
    vector<vector<int>> route(n);
    for(int i=0; i<n; i++)
    {
        int num; cin >> num;
        vector<int> temp(num);
        for(int j=0; j<num; j++) cin >> temp[j];
        route[i] = temp;
    }
    minTramsToReach(route, source, target);

    // vector<vector<pair<int,int>>> adj(m+1);
    // for(int i=0; i<n; i++)
    // {
    //     for(int j=0; j<route[i].size(); j++)
    //     {
    //         adj[route[i][j]].push_back({route[i][(j+1)%route[i].size()], i});
    //         adj[route[i][(j+1)%route[i].size()]].push_back({route[i][j], i});
    //     }
    // }
    // vector<int> dist(m+1, INT_MAX);
    // dist[source] = 0;
    // priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    // pq.push({0, source});
    // vector<int> par(m+1, -1);
    // while(!pq.empty())
    // {
    //     auto [d, u] = pq.top(); pq.pop();
    //     if(d != dist[u]) continue;
    //     if(u == target) break;
    //     for(auto &e : adj[u])
    //     {
    //         int v = e.first;
    //         int routeIdx = e.second;
    //         int w = (par[u] == routeIdx) ? 0 : 1;
    //         int nd = d + w;
    //         if(nd < dist[v])
    //         {
    //             dist[v] = nd;
    //             par[v] = routeIdx;
    //             pq.push({nd, v});
    //         }
    //     }
    // }
    // if(dist[target] == INT_MAX) cout << -1;
    // else cout << dist[target];
}