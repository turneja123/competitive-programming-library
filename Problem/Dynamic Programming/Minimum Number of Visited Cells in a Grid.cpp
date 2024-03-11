//https://leetcode.com/problems/minimum-number-of-visited-cells-in-a-grid/
class Solution {
public:
    int minimumVisitedCells(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 0));

        multiset<int> rowmin;
        multiset<int> colmin[m];
        priority_queue<pair<int, int>> rowq;
        priority_queue<pair<int, int>> colq[m];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                while (rowq.size() && -rowq.top().first < j) {
                    int jmin = rowq.top().second;
                    rowmin.erase(rowmin.find(dp[i][jmin]));
                    rowq.pop();
                }
                while (colq[j].size() && -colq[j].top().first < i) {
                    int imin = colq[j].top().second;
                    colmin[j].erase(colmin[j].find(dp[imin][j]));
                    colq[j].pop();
                }

                dp[i][j] = m * n + 1;
                if (rowmin.size()) {
                    dp[i][j] = min(dp[i][j], *rowmin.begin() + 1);
                }
                if (colmin[j].size()) {
                    dp[i][j] = min(dp[i][j], *colmin[j].begin() + 1);
                }
                if (i == 0 && j == 0) {
                    dp[i][j] = 1;
                }
                rowmin.insert(dp[i][j]);
                colmin[j].insert(dp[i][j]);
                rowq.push(make_pair(-(j + grid[i][j]), j));
                colq[j].push(make_pair(-(i + grid[i][j]), i));
            }
            while (rowq.size()) {
                rowq.pop();
            }
            rowmin.clear();
        }
        if (dp[n - 1][m - 1] == m * n + 1) {
            return -1;
        }
        return dp[n - 1][m - 1];
    }
};