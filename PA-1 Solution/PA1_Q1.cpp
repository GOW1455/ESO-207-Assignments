#include <iostream>
#include <vector>
using namespace std;

int gcd(int a, int b) {
    while(b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

void buildsparse(vector<int> &a, int n, vector<vector<int>> &sparse) {
    int maxlog = 32 - __builtin_clz(n);
    sparse.assign(maxlog, vector<int>(n));
    for (int i = 0; i < n; i++) sparse[0][i] = a[i];
    for (int k = 1; k < maxlog; k++) {
        for (int i = 0; i + (1 << k) <= n; i++) {
            sparse[k][i] = gcd(sparse[k-1][i], sparse[k-1][i + (1 << (k-1))]);
        }
    }
}

int query(int l, int r, const vector<vector<int>> &sparse) {
    int k = 31 - __builtin_clz(r - l + 1);
    return gcd(sparse[k][l], sparse[k][r - (1 << k) + 1]);
}

long long countsubarrays(vector<int> &a, int m){
    int n = a.size();
    vector<vector<int>> sparse;
    buildsparse(a, n, sparse);
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int j = i;
        while(j<n)
        {
            int g = query(i, j, sparse);
            if(g<m || g%m!=0) {
                break;
            }
            int l = j, r = n-1, pos = j;
            while(l<=r)
            {
                int mid = (l+r)/2;
                if(query(i, mid, sparse)==g)
                {
                    pos = mid;
                    l = mid+1;
                }
                else
                {
                    r = mid-1;
                }
            }
            if(g==m) ans += (pos-j+1);
            j = pos+1;
        }
    }
    return ans;
}

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cout << countsubarrays(a, m) << endl;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int t; cin >> t;
    while(t--) solve();
    return 0;
}