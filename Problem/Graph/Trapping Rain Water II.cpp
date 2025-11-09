//https://leetcode.com/problems/trapping-rain-water-ii/description/
const int INF = 1e9;
class Solution {
public:

    int trapRainWater(vector<vector<int>>& a) {
        int n = a.size(), m = a[0].size();
        vector<vector<int>> ans(n, vector<int>(m, INF));
        priority_queue<tuple<int, int, int>> pq;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0 || j == 0 || i == n - 1 || j == m - 1) {
                    ans[i][j] = 0;
                    pq.push(make_tuple(0, i, j));
                }
            }
        }
        while (pq.size()) {
            auto [d, x, y] = pq.top();
            pq.pop();
            d = -d;
            if (d != ans[x][y]) {
                continue;
            }
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (abs(dx) + abs(dy) == 1 && x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < m) {
                        if (max(ans[x][y], a[x][y]) < ans[x + dx][y + dy]) {
                            ans[x + dx][y + dy] = max(ans[x][y], a[x][y]);
                            pq.push({-ans[x + dx][y + dy], x + dx, y + dy});
                        }
                    }
                }
            }
        }
        int sum = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                sum += max(0, ans[i][j] - a[i][j]);
            }
        }

        return sum;
    }
};
