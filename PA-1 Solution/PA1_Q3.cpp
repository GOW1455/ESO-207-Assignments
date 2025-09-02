#include <iostream>
#include <vector>
using namespace std;

const long long MOD = 1e9+7;

vector<vector<long long>> matmul(vector<vector<long long>> &a, vector<vector<long long>> &b) {
    int n = a.size();
    int m = a[0].size();
    int p = b[0].size();
    vector<vector<long long>> c(n, vector<long long>(p, 0));
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<p; j++)
        {
            long long sum = 0;
            for(int k=0; k<m; k++)
            {
                sum = (sum + (a[i][k] * b[k][j]) % MOD) % MOD;
            }
            c[i][j] = sum;
        }
    }
    return c;
}

vector<vector<long long>> matpow(vector<vector<long long>> &m, int d) {
    int k = m.size();
    vector<vector<long long>> res(k, vector<long long>(k, 0));
    for(int i=0; i<k; i++)
    {
        res[i][i] = 1;
    }
    vector<vector<long long>> base = m;
    while(d)
    {
        if(d % 2 == 1) {
            res = matmul(res, base);
        }
        base = matmul(base, base);
        d >>= 1;
    }
    return res;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n, k, d; 
    cin >> n >> k >> d;
    vector<vector<long long>> mat(k, vector<long long>(k, 0));
    for(int i=0; i<k; i++)
    {
        mat[0][i] = i+1;
    }
    for(int i=1; i<k; i++)
    {
        mat[i][i-1] = 1;
    }
    vector<vector<long long>> start(k, vector<long long>(1, 0));
    start[0][0] = n % MOD;

    vector<vector<long long>> matd = matpow(mat, d);
    vector<vector<long long>> ans = matmul(matd, start);

    long long result = 0;
    for(int i=0; i<k; i++)
    {
        result = (result + ans[i][0]) % MOD;
    }
    cout << result << endl;
    return 0;
}
