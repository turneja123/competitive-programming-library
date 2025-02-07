//https://leetcode.com/contest/weekly-contest-215/problems/maximize-grid-happiness/
const int N = 10;
const int K = 250;
int dp[N][N][N][K];
class Solution {
public:
    int value[K];
    int ctx[K], cty[K];
    int pw[N];
    vector<int> col[K];
    int cost[K][K];

    int getMaxGridHappiness(int n, int m, int x, int y) {
        if (n > m) {
            swap(n, m);
        }
        pw[0] = 1;
        for (int i = 1; i <= n; i++) {
            pw[i] = pw[i - 1] * 3;
        }
        for (int i = 0; i < m; i++) {
            for (int a = 0; a <= x; a++) {
                for (int b = 0; b <= y; b++) {
                    for (int mask = 0; mask < pw[n]; mask++) {
                        dp[i][a][b][mask] = -1;
                    }
                }
            }
        }
        for (int mask = 0; mask < pw[n]; mask++) {
            vector<int> v(n, 0);
            int j = mask;
            for (int k = 0; k < n; k++) {
                v[k] = j % 3;
                j /= 3;
            }
            for (int k = 0; k < n; k++) {
                if (v[k] == 1) {
                    value[mask] += 120;
                    if (k > 0 && v[k - 1] > 0) {
                        value[mask] -= 30;
                    }
                    if (k < n - 1 && v[k + 1] > 0) {
                        value[mask] -= 30;
                    }
                    ctx[mask]++;
                } else if (v[k] == 2) {
                    value[mask] += 40;
                    if (k > 0 && v[k - 1] > 0) {
                        value[mask] += 20;
                    }
                    if (k < n - 1 && v[k + 1] > 0) {
                        value[mask] += 20;
                    }
                    cty[mask]++;
                }
            }
            if (ctx[mask] <= x && cty[mask] <= y) {
                dp[0][ctx[mask]][cty[mask]][mask] = value[mask];
            }
            col[mask] = v;
        }
        for (int ma = 0; ma < pw[n]; ma++) {
            for (int mb = 0; mb < pw[n]; mb++) {
                for (int i = 0; i < n; i++) {
                    if (col[ma][i] == 1 && col[mb][i] > 0) {
                        cost[ma][mb] -= 30;
                    }
                    if (col[ma][i] == 2 && col[mb][i] > 0) {
                        cost[ma][mb] += 20;
                    }

                    if (col[mb][i] == 1 && col[ma][i] > 0) {
                        cost[ma][mb] -= 30;
                    }
                    if (col[mb][i] == 2 && col[ma][i] > 0) {
                        cost[ma][mb] += 20;
                    }
                }
            }
        }

        for (int i = 1; i < m; i++) {
            for (int a = 0; a <= x; a++) {
                for (int b = 0; b <= y; b++) {
                    for (int prv = 0; prv < pw[n]; prv++) {
                        if (dp[i - 1][a][b][prv] == -1) {
                            continue;
                        }
                        for (int mask = 0; mask < pw[n]; mask++) {
                            if (a + ctx[mask] > x || b + cty[mask] > y) {
                                continue;
                            }
                            dp[i][a + ctx[mask]][b + cty[mask]][mask] = max(dp[i][a + ctx[mask]][b + cty[mask]][mask],
                                                                           dp[i - 1][a][b][prv] + value[mask] + cost[prv][mask]);
                        }
                    }
                }
            }
        }
        int ans = 0;
        for (int a = 0; a <= x; a++) {
            for (int b = 0; b <= y; b++) {
                for (int mask = 0; mask < pw[n]; mask++) {
                    ans = max(ans, dp[m - 1][a][b][mask]);
                }
            }
        }
        return ans;
    }
};
