#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main()
{
    int n, d, t; cin >> n >> d >> t;
    vector<pair<int, int>> players(n);
    for(int i=0; i<n; i++)
    {
        cin >> players[i].first >> players[i].second;
    }
    sort(players.begin(), players.end());
    queue<pair<int, int>> q;
    int ans = 0;
    for(int i=0; i<n ; i++)
    {
        int temp = players[i].first;
        while(!q.empty() && q.front().first<temp-d)
        {
            auto p = q.front(); q.pop();
            if(p.first + p.second <= temp) ans++;
        }
        q.push(players[i]);
    }
    while(!q.empty())
    {
        auto p = q.front(); q.pop();
        if(p.first + p.second <= t) ans++;
    }
    cout << ans << endl;
    return 0;
}