//https://leetcode.com/problems/maximum-strictly-increasing-cells-in-a-matrix/description/
const int INF = 1e9;
class Solution {
public:
    int maxIncreasingCells(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<pair<int, pair<int, int>>> v;
        vector<vector<int>> dp(n, vector<int>(m, 1));
        vector<int> row(n, 0);
        vector<int> col(m, 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                v.push_back(make_pair(grid[i][j], make_pair(i, j)));
            }
        }
        sort(v.begin(), v.end());
        int ans = 0; int last = -INF;
        vector<pair<int, pair<int, int>>> add;
        for (int i = 0; i < n * m; i++) {
            int x = v[i].second.first, y = v[i].second.second, cur = v[i].first;
            if (last != -INF && last != cur) {
                for (int j = 0; j < add.size(); j++) {
                    int d = add[j].first, dx = add[j].second.first, dy = add[j].second.second;
                    row[dx] = max(row[dx], d);
                    col[dy] = max(col[dy], d);
                }
                add.clear();
                last = cur;
            } else {
                last = cur;
            }
            dp[x][y] = max({dp[x][y], row[x] + 1, col[y] + 1});
            add.push_back(make_pair(dp[x][y], make_pair(x, y)));
            ans = max(ans, dp[x][y]);
        }
        return ans;
    }
};
