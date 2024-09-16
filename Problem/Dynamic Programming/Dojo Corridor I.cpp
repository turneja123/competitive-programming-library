//https://www.spoj.com/problems/DOJ1/
#pragma GCC optimize("Ofast,fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3;
const int M = 6;
const long long MOD  = 1e9 + 7;

long long dp[N][M][1 << N];
long long dp_pre[N][M][1 << N];
vector<long long> s[1 << N];
vector<long long> c;

using ll = long long;

int idx = 0;
vector<long long> temp[32];

long long mul(long long x, long long y, long long m){
    long long k = (x * (double)y / m) + 0.5, r = x * y - k * m;
    return r < 0 ? r + m : r;
}

vector<long long> mul(int n, vector<long long> &a, vector<long long> &b, vector<long long> &tr, long long M) {
    vector<long long> res(n * 2 + 1, 0);
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            res[i + j] = (res[i + j] + mul(a[i], b[j], M));
        }
    }
    for (int i = 2 * n; i > n; --i) {
        res[i] %= M;
        for (int j = 0; j < n; j++) {
            res[i - 1 - j] = (res[i - 1 - j] + mul(res[i], tr[j], M));
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        res[i] %= M;
    }
    res.resize(n + 1);
    return res;
}

long long solve(vector<long long> &c, vector<long long> &s, long long k, long long M) {
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
            x = mul(n, x, a, c, M);
        }
        if (idx < j) {
            a = mul(n, a, a, c, M);
            temp[++idx] = a;
        } else {
            a = temp[j];
        }
    }
    long long res = 0;
    for (int i = 0; i < n; i++) {
        res = (res + x[i + 1] * s[i]);
    }
    return res % M;
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
    dp_pre[0][0][6] = 1;

    for (int j = 0; j < M; j++) {
        for (int i = 0; i < 3; i++) {
            if (i == 0 && j == 0) {
                continue;
            }
            for (int mask = 0; mask < 8; mask++) {
                if (i == 0) {
                    dp_pre[i][j][mask] = dp_pre[2][j - 1][mask ^ (1 << i)];
                } else {
                    dp_pre[i][j][mask] = dp_pre[i - 1][j][mask ^ (1 << i)];
                    if ((mask & (1 << i)) && (mask & (1 << i - 1))) {
                        dp_pre[i][j][mask] += dp_pre[i - 1][j][mask ^ (1 << i - 1)];
                    }
                }
            }
        }
    }
}

int main() {
    IOS;
    precalc();
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        idx = 0;
        int n, m, x, y; long long k;
        cin >> n >> m >> x >> y >> k;
        if (k == 1) {
            cout << 0 << endl;
            continue;
        }
        if (n == 1) {
            if ((y - 1) % 2 == 0 && (m - y) % 2 == 0) {
                cout << 1 << endl;
            } else {
                cout << 0 << endl;
            }
            continue;
        }
        if (n == 2 || n == 4) {
            cout << 0 << endl;
            continue;
        }
        if (m % 2 == 0) {
            cout << 0 << endl;
            continue;
        }
        c = {0, 4 % k, 0, (-1 + k) % k};
        for (int i = 0; i < 8; i++) {
            s[i].clear();
        }
        x--, y--;
        if (y != 0) {
            for (int j = 0; j < 4; j++) {
                for (int mask = 0; mask < 1 << n; mask++) {
                    s[mask].push_back(dp_pre[n - 1][j][mask] % k);
                }
            }
            for (int mask = 0; mask < 1 << n; mask++) {
                if (mask == 2 || mask == 5) {
                    continue;
                }
                dp[n - 1][0][mask] = solve(c, s[mask], y - 1, k);
                s[mask].clear();
            }
            dp[n - 1][0][2] = 0, dp[n - 1][0][5] = 0;
        }
        for (int j = 1; j < M; j++) {
            for (int i = 0; i < n; i++) {
                if (i == 0 && j == 0) {
                    continue;
                }
                for (int mask = 0; mask < 1 << n; mask++) {
                    if (x == i && j == 1) {
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
                }
            }
            for (int mask = 0; mask < 1 << n; mask++) {
                s[mask].push_back(dp[n - 1][j][mask] % k);
            }
        }
        cout << solve(c, s[7], m - y - 1, k) << endl;
        reset(n);
    }
    return 0;
}
