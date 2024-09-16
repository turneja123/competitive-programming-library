//https://www.spoj.com/problems/DOJ2/
#pragma GCC optimize("Ofast,fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5;
const int M = 8;
const long long MOD = 1e9 + 7;

long long dp[N][M][1 << N];
long long dp_pre[N][M][1 << N];
vector<long long> s[1 << N];
vector<long long> c;

using ll = long long;

int idx = 0;
vector<long long> temp[32];
vector<int> v{2, 5, 8, 10, 11, 14, 17, 20, 21, 23, 26, 29};
bool can[32];

vector<long long> mul(int n, vector<long long> &a, vector<long long> &b, vector<long long> &tr) {
    vector<long long> res(n * 2 + 1, 0);
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            res[i + j] = (res[i + j] + a[i] * b[j]) % MOD;
        }
    }
    for (int i = 2 * n; i > n; --i) {
        for (int j = 0; j < n; j++) {
            res[i - 1 - j] = (res[i - 1 - j] + res[i] * tr[j]) % MOD;
        }
    }
    res.resize(n + 1);
    return res;
}

long long solve(vector<long long> &c, vector<long long> &s, long long k) {
    int n = c.size();
    if (n == 0) {
        return 0;
    }
    if (k < n) {
        return s[k];
    }
    vector<long long> x(n + 1), a(x);
    x[0] = 1, a[1] = 1; int j = 1;
    for (++k; k; k /= 2, j++) {
        if (k % 2) {
            x = mul(n, x, a, c);
        }
        if (idx < j) {
            a = mul(n, a, a, c);
            temp[++idx] = a;
        } else {
            a = temp[j];
        }
    }
    long long res = 0;
    for (int i = 0; i < n; i++) {
        res = (res + x[i + 1] * s[i]) % MOD;
    }
    return res % MOD;
}

void reset(int n) {
    for (int j = 0; j < M; j++) {
        for (int i = 0; i < n; i++) {
            for (int mask = 0; mask < 1 << n; mask++) {
                dp[i][j][mask] = 0;
            }
        }
    }
    return;
}

void precalc() {
    for (int x : v) {
        can[x] = true;
    }
    c = {0, 15, 0, 999999975, 0, 15, 0, 1000000006};
    dp_pre[0][0][30] = 1;
    for (int j = 0; j < M; j++) {
        for (int i = 0; i < 5; i++) {
            if (i == 0 && j == 0) {
                continue;
            }
            for (int mask = 0; mask < 32; mask++) {
                if (i == 0) {
                    dp_pre[i][j][mask] = dp_pre[4][j - 1][mask ^ (1 << i)];
                } else {
                    dp_pre[i][j][mask] = dp_pre[i - 1][j][mask ^ (1 << i)];
                    if ((mask & (1 << i)) && (mask & (1 << i - 1))) {
                        dp_pre[i][j][mask] += dp_pre[i - 1][j][mask ^ (1 << i - 1)];
                    }
                }
            }
        }
        for (int mask = 0; mask < 32; mask++) {
            s[mask].push_back(dp_pre[4][j][mask] % MOD);
        }
    }
    for (int mask = 0; mask < 32; mask++) {
        if (can[mask]) {
            continue;
        }
        for (int i = 8; i <= 20000; i++) {
            long long nw = 0;
            for (int j = 0; j < 8; j++) {
                nw = (nw + s[mask][i - j - 1] * c[j]) % MOD;
            }
            s[mask].push_back(nw);
        }
    }
}


int main() {
    IOS;
    precalc();
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int n = 5, m, x, y; char ch;
        cin >> m >> ch >> y;
        x = ch - 'A';
        if (m % 2 == 0) {
            cout << 0 << endl;
            continue;
        }
        y--;
        int start = 0;
        if (y != 0) {
            for (int mask = 0; mask < 1 << n; mask++) {
                if (can[mask]) {
                    dp[n - 1][0][mask] = 0;
                    continue;
                }
                dp[n - 1][0][mask] = s[mask][y - 1];
            }
            start = 1;
        } else {
            if (x != 0) {
                dp[0][0][30] = 1;
            } else {
                dp[0][0][31] = 1;
            }
        }
        vector<long long> ans;
        for (int j = start; j < M + start; j++) {
            for (int i = 0; i < n; i++) {
                if (i == 0 && j == 0) {
                    continue;
                }
                for (int mask = 0; mask < 1 << n; mask++) {
                    if (x == i && j == start) {
                        if (!(mask & (1 << i))) {
                            dp[i][j][mask] = 0;
                        } else {
                            if (i == 0) {
                                dp[i][j][mask] = dp[n - 1][j - 1][mask];
                            } else {
                                dp[i][j][mask] = dp[i - 1][j][mask];
                            }
                        }
                        continue;
                    }
                    if (i == 0) {
                        dp[i][j][mask] = dp[n - 1][j - 1][mask ^ (1 << i)];
                    } else {
                        dp[i][j][mask] = dp[i - 1][j][mask ^ (1 << i)];
                        if ((mask & (1 << i)) && (mask & (1 << i - 1))) {
                            dp[i][j][mask] += dp[i - 1][j][mask ^ (1 << i - 1)];
                        }
                    }
                    dp[i][j][mask] %= MOD;
                }
            }
            ans.push_back(dp[n - 1][j][31] % MOD);
        }
        cout << solve(c, ans, m - y - 1) << endl;
        reset(n);
    }
    return 0;
}
