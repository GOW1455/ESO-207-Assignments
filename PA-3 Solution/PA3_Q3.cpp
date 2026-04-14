#include <iostream>
#include <vector>
using namespace std;

int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

bool valid(int x, int y, int m, int n, vector<vector<int>> &grid) {
    return x >= 0 && y >= 0 && x < m && y < n && grid[x][y] == 1;
}

void dfs(int x, int y, int px, int py, bool isRoot, int &timer, 
         vector<vector<int>> &grid, vector<vector<int>> &vis,
         vector<vector<int>> &tin, vector<vector<int>> &low, bool &articulation) {
    
    vis[x][y] = 1;
    tin[x][y] = low[x][y] = ++timer;
    int childCount = 0;
    int m = grid.size(), n = grid[0].size();

    for (auto &d : dirs)
    {
        int nx = x + d[0], ny = y + d[1];
        if (!valid(nx, ny, m, n, grid)) continue;

        if (!vis[nx][ny])
        {
            childCount++;
            dfs(nx, ny, x, y, false, timer, grid, vis, tin, low, articulation);
            low[x][y] = min(low[x][y], low[nx][ny]);
            if (!isRoot && low[nx][ny] >= tin[x][y])
                articulation = true;
        }
        else if (!(nx == px && ny == py))
        {
            low[x][y] = min(low[x][y], tin[nx][ny]);
        }
    }

    if (isRoot && childCount > 1) articulation = true;
}

int main()
{
    int n, m; cin >> n >> m;
    vector<vector<int>> matrix(n, vector<int>(m));
    int land = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> matrix[i][j];
            land += matrix[i][j];
        }
    }
    if(land == 1)
    {
        cout << 1 << endl;
        return 0;
    }
    
    vector<vector<int>> visited(n, vector<int>(m, 0)), tin(n, vector<int>(m, 0)), low(n, vector<int>(m, 0));
    int islands = 0, timer = 0;
    bool articulation = false;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(matrix[i][j] == 1 && !visited[i][j])
            {
                islands++;
                if(islands > 1)
                {
                    cout << 0 << endl;
                    return 0;
                }
                dfs(i, j, -1, -1, true, timer, matrix, visited, tin, low, articulation);
            }
        }
    }
    if(islands == 0) cout << 0 << endl;
    else if(articulation) cout << 1 << endl;
    else cout << 2 << endl;

}