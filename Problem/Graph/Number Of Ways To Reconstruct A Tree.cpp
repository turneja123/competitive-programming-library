//https://leetcode.com/contest/biweekly-contest-43/problems/number-of-ways-to-reconstruct-a-tree/
const int N = 505;
class Solution {
public:
    bool g[N][N];
    int id[N];
    int deg[N];
    int checkWays(vector<vector<int>>& pairs) {
        for (int i = 0; i < N; i++) {
            id[i] = -1;
        }
        int n = 0;
        for (int i = 0; i < pairs.size(); i++) {
            int x = pairs[i][0], y = pairs[i][1];
            if (id[x] == -1) {
                id[x] = n++;
            }
            if (id[y] == -1) {
                id[y] = n++;
            }
            x = id[x], y = id[y];
            pairs[i][0] = x, pairs[i][1] = y;
            g[x][y] = true, g[y][x] = true;
            deg[x]++, deg[y]++;
        }
        int root = 0;
        for (int i = 0; i < n; i++) {
            g[i][i] = true;
            deg[i]++;
            if (deg[i] == n) {
                root = 1;
            }
        }
        if (!root) {
            return 0;
        }
        int db = 0;
        for (int i = 0; i < pairs.size(); i++) {
            int x = pairs[i][0], y = pairs[i][1];
            if (deg[x] > deg[y]) {
                swap(x, y);
            }
            if (deg[x] == deg[y]) {
                db = 1;
            }
            for (int j = 0; j < n; j++) {
                if (g[x][j] && !g[y][j]) {
                    return 0;
                }
            }
        }
        return db ? 2 : 1;
    }
};
