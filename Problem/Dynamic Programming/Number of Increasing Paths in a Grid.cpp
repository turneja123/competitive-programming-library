//https://leetcode.com/problems/number-of-increasing-paths-in-a-grid/description/?envType=problem-list-v2&envId=topological-sort
const int N = 1005;
const long long M = 1e9 + 7;
long long dp[N][N];
class Solution {
public:
    int countPaths(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<pair<int, pair<int, int>>> v;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                v.push_back(make_pair(grid[i][j], make_pair(i, j)));
                dp[i][j] = 1;
            }
        }
        sort(v.begin(), v.end());
        long long ans = 0;
        for (int i = 0; i < n * m; i++) {
            int x = v[i].second.first, y = v[i].second.second;
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (abs(dx) + abs(dy) == 1 && x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < m && grid[x][y] < grid[x + dx][y + dy]) {
                        dp[x + dx][y + dy] = (dp[x + dx][y + dy] + dp[x][y]) % M;
                    }
                }
            }
            ans += dp[x][y];
        }
        return ans % M;
    }
};
