#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m; 
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> grid[i][j];
        }
    }
    int maxsum = grid[0][0], maxleft = 0, maxright = 0, maxtop = 0, maxbottom = 0;
    for (int l=0; l<m; l++)
    {
        vector<int> row_sum(n, 0);
        for (int r=l; r<m;r++)
        {
            for (int i=0; i<n; i++)
            {
                row_sum[i] += grid[i][r];
            }
            int cursum = 0, curtop = 0;
            for (int i=0; i<n; i++)
            {
                cursum += row_sum[i];
                if (cursum > maxsum)
                {
                    maxsum = cursum;
                    maxleft = l;
                    maxright = r;
                    maxtop = curtop;
                    maxbottom = i;
                }
                if (cursum < 0)
                {
                    cursum = 0;
                    curtop = i + 1;
                }
            }
        }
    }
    if (maxsum < 0) cout << "NO" << endl;
    else
    {
        cout << "YES" << endl;
        cout << maxsum << endl;
        cout << maxtop + 1 << " " << maxleft + 1 << " " << maxbottom + 1 << " " << maxright + 1 << endl;
    }
    return 0;
}
