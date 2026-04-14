#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    int n; cin >> n;
    vector<int> arr(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        arr[i] %= 12;
    }

    vector<vector<int>> adj(n + 1);
    for(int i=0; i<n-1; i++)
    {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    int sum0 = 0, sum1 = 0;
    int cnt0 = 0, cnt1 = 0;

    vector<int> visited(n + 1, 0);
    vector<int> col(n + 1, -1);
    queue<int> q;

    q.push(1);
    col[1] = 0;
    visited[1] = 1;
    while (!q.empty())
    {
        int node = q.front(); q.pop();
        if(col[node] == 0) {
            sum0 += arr[node];
            cnt0++;
        }
        else
        {
            sum1 += arr[node];
            cnt1++;
        }
        for (int v : adj[node])
        {
            if (col[v] == -1)
            {
                col[v] = 1 - col[node];
                q.push(v);
            }
        }
    }
    int ans = 0;
    sum0 %= 12;
    sum1 %= 12;
    if(sum0 == sum1) ans = n;
    else if((sum0 + 1)%12 == sum1) ans = cnt1;
    else if((sum1 + 1)%12 == sum0) ans = cnt0;
    cout << ans << endl;
}