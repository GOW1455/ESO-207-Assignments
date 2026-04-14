#include<bits/stdc++.h>
using namespace std;
#define int long long

bool good(int n, int r, vector<pair<int,int>> &lights)
{
    vector<vector<int>> diff(n+2, vector<int>(n+2, 0));
    for (auto &p:lights)
    {
        int x = p.first;
        int y = p.second;
        int x1 = max(1LL, x-r);
        int x2 = min(n, x+r);
        int y1 = max(1LL, y-r);
        int y2 = min(n, y+r);

        diff[x1][y1] += 1;
        diff[x1][y2+1] -= 1;
        diff[x2+1][y1] -= 1;
        diff[x2+1][y2+1] += 1;
    }
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++)
        {
            diff[i][j] += diff[i-1][j] + diff[i][j-1] - diff[i-1][j-1];
            if (diff[i][j] <= 0) return false;
        }
    }
    return true;
}

void solve()
{
    int n, k; cin >> n >> k;
    vector<pair<int, int>> lights(k);
    for(int i=0; i<k; i++)
    {
        cin >> lights[i].first >> lights[i].second;
    }
    int low = 0, high = n, ans = n;
    while(low<=high)
    {
        int mid = (low+high)/2;
        if(good(n, mid, lights))
        {
            ans = mid;
            high = mid-1;
        }
        else
        {
            low = mid+1;
        }
    }
    cout << ans << endl;
}

signed main()
{
    int t; cin >> t;
    while(t--){
        solve();
    }
    return 0;
}