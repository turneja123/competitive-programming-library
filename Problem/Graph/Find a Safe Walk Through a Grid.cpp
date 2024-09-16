//https://leetcode.com/contest/biweekly-contest-139/problems/find-a-safe-walk-through-a-grid/
class Solution {
public:
    bool dist[50][50][105];
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int n = grid.size(), m = grid[0].size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int k = 0; k <= n + m; k++) {
                    dist[i][j][k] = 0;
                }
            }
        }
        queue<tuple<int, int, int>> q;
        q.push(make_tuple(0, 0, health - grid[0][0]));
        dist[0][0][health - grid[0][0]] = 0;
        while (q.size()) {
            tuple<int, int, int> t = q.front();
            q.pop();
            int x = get<0>(t), y = get<1>(t), k = get<2>(t);
            if (k == 0) {
                continue;
            }
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (abs(dx) + abs(dy) != 1 || x + dx < 0 || x + dx == n || y + dy < 0 || y + dy == m) {
                        continue;
                    }
                    int kk = k - grid[x + dx][y + dy];
                    if (dist[x + dx][y + dy][kk] == 1 || kk == 0) {
                        continue;
                    }
                    q.push(make_tuple(x + dx, y + dy, kk));
                    dist[x + dx][y + dy][kk] = 1;
                }
            }
        }
        bool ans = false;
        for (int k = 1; k <= n + m; k++) {
            if (dist[n - 1][m - 1][k]) {
                ans = true;
            }
        }
        return ans;
    }
};
