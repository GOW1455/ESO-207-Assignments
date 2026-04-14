#include <bits/stdc++.h>
using namespace std;
#define int long long

const int mod = 998244353;

int modpow(int a, int e){
    int r = 1;
    while(e){
        if(e & 1) r = r * a % mod;
        a = a * a % mod;
        e >>= 1;
    }
    return r;
}

int prod_avail(vector<int>& a, set<int>& s, int l, int r){
    if(l > r) return 1;
    if(l == r)
    {
        s.insert(a[l]);
        return a[l];
    }
    if(a[l] == a[r])
    {
        int x = modpow(a[l], r - l + 1);
        s.insert(x);
        return x;
    }

    int mid = (a[l] + a[r]) / 2;
    int j = upper_bound(a.begin() + l, a.begin() + r + 1, mid) - a.begin() - 1;

    int prodleft  = prod_avail(a, s, l, j);
    int prodright = prod_avail(a, s, j+1, r);

    int prod = (prodleft * prodright) % mod;
    s.insert(prod);
    return prod;
}

void solve(){
    int n, q; cin >> n >> q;
    
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());

    set<int> s;
    prod_avail(a, s, 0, n-1);

    while(q--)
    {
        int x; cin >> x;
        if(s.find(x) != s.end()) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
}

signed main()
{
    int t; cin >> t;
    while(t--) solve();
    return 0;
}