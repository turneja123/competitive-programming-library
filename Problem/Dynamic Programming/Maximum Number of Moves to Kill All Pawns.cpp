//https://leetcode.com/contest/weekly-contest-414/problems/maximum-number-of-moves-to-kill-all-pawns/
int has = 0;
int dist[2500][2500];
vector<pair<int, int>> moves{{1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};
const int K = 16;
class Solution {
public:
    int dp[K][1 << K];
    void precalc() {
        for (int i = 0; i < 2500; i++) {
            for (int j = 0; j < 2500; j++) {
                dist[i][j] = 1e9;
            }
        }
        for (int i = 0; i < 50; i++) {
            for (int j = 0; j < 50; j++) {
                int cur = i * 50 + j;
                queue<int> q;
                dist[cur][cur] = 0;
                q.push(cur);

                while (q.size()) {
                    int c = q.front();
                    q.pop();
                    int x = c / 50, y = c % 50;
                    for (int d = 0; d < 8; d++) {
                        int dx = x + moves[d].first, dy = y + moves[d].second;
                        if (dx >= 0 && dx < 50 && dy >= 0 && dy < 50) {
                            int nx = dx * 50 + dy;
                            if (dist[cur][nx] > dist[cur][c] + 1) {
                                dist[cur][nx] = dist[cur][c] + 1;
                                q.push(nx);
                            }
                        }
                    }
                }
            }
        }
        has = 1;
    }
    int get(vector<int> &a) {
        return a[0] * 50 + a[1];
    }

    int calc(int i, int n, int last, int mask, vector<vector<int>>& a) {
        if (dp[last][mask] != 0) {
            return dp[last][mask];
        }
        if (i == n) {
            return 0;
        }
        int ans;
        if (i % 2 == 1) {
            ans = 1e9;
            for (int j = 0; j < n; j++) {
                int c = mask & (1 << j);
                if (c == 0) {
                    ans = min(ans, dist[get(a[last])][get(a[j])] + calc(i + 1, n, j, mask | (1 << j), a));
                }
            }
        } else {
            ans = 0;
            for (int j = 0; j < n; j++) {
                int c = mask & (1 << j);
                if (c == 0) {
                    ans = max(ans, dist[get(a[last])][get(a[j])] + calc(i + 1, n, j, mask | (1 << j), a));
                }
            }
        }
        return dp[last][mask] = ans;
    }

    int maxMoves(int kx, int ky, vector<vector<int>>& a) {
        if (has == 0) {
            precalc();
        }
        int n = a.size(), ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, dist[kx * 50 + ky][get(a[i])] + calc(1, n, i, 1 << i, a));
        }

        return ans;
    }
};
