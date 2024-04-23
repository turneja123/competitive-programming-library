//https://www.spoj.com/problems/TRKNIGHT/
#pragma GCC optimize("Ofast,fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

long long M;
vector<long long> m{29, 34483};
const long long N = 50;

long long dp[N][N];
long long dp_next[N][N];

vector<pair<int, int>> moves{{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

long long extendedEuclidean(long long a, long long b, long long *x, long long *y) {
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }
    long long x1, y1;
    long long gcd = extendedEuclidean(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}

long long modInverse(long long b, long long m) {
    long long x, y;
    long long g = extendedEuclidean(b, m, &x, &y);
    if (g != 1) {
        return -1;
    }
    return (x % m + m) % m;
}

long long crt(vector<pair<long long, long long>> &v) {
    long long M = 1;
    for (int i = 0; i < v.size(); i++) {
        M *= v[i].second;
    }
    __int128 ans = 0;
    for (int i = 0; i < v.size(); i++) {
        long long m = M / v[i].second;
        long long n = modInverse(m, v[i].second);
        ans = (ans + (__int128)v[i].first * m % M * n) % M;
    }
    return (long long)ans;
}

vector<long long> mul(int n, vector<long long> &a, vector<long long> &b, vector<long long> &tr) {
    vector<long long> res(n * 2 + 1, 0);
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            res[i + j] = (res[i + j] + a[i] * b[j]) % M;
        }
    }
    for (int i = 2 * n; i > n; --i) {
        for (int j = 0; j < n; j++) {
            res[i - 1 - j] = (res[i - 1 - j] + res[i] * tr[j]) % M;
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
    x[0] = 1, a[1] = 1;
    for (++k; k; k /= 2) {
        if (k % 2) {
            x = mul(n, x, a, c);
        }
        a = mul(n, a, a, c);
    }
    long long res = 0;
    for (int i = 0; i < n; i++) {
        res = (res + x[i + 1] * s[i]) % M;
    }
    return res;
}

long long modPow(long long a, long long y) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

vector<long long> berlekamp_massey(vector<long long> s) {
    int n = s.size(), l = 0, m = 0;
    vector<long long> c(n), b(n), t(n);
    c[0] = 1, b[0] = 1;
    long long d = 1;
    for (int i = 0; i < n; i++) {
        m++;
        long long d_next = s[i];
        for (int j = 1; j <= l; j++) {
            d_next = (d_next + (c[j] * s[i - j]) % M) % M;
        }
        if (d_next == 0) {
            continue;
        }
        t = c;
        long long coef = (d_next * modPow(d, M - 2)) % M;
        for (int j = m; j < n; j++) {
            c[j] = (c[j] - (coef * b[j - m]) % M + M) % M;
        }
        if (2 * l > i) {
            continue;
        }
        l = i + 1 - l, b = t, d = d_next, m = 0;
    }
    c.resize(l + 1);
    c.erase(c.begin());
    for (int i = 0; i < l; i++) {
        c[i] *= -1;
        c[i] = (c[i] + M) % M;
    }
    return c;
}

int main() {
    IOS;
    int t = 400;
    vector<vector<long long>> s[2];
    vector<vector<long long>> c[2];
    for (int i = 0; i < 2; i++) {
        s[i].resize(50, vector<long long>(t));
        c[i].resize(50, vector<long long>(t));
    }
    for (int q = 0; q < 2; q++) {
        M = m[q];
        for (int n = 4; n <= 24; n += 2) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    dp[i][j] = 0;
                }
            }
            dp[0][0] = 1;
            s[q][n][0] = 1;
            for (int k = 1; k <= t; k++) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        for (int p = 0; p < 8; p++) {
                            int y = i + moves[p].first, x = j + moves[p].second;
                            if (y >= 0 && y < n && x >= 0 && x < n) {
                                dp_next[y][x] = (dp_next[y][x] + dp[i][j]) % M;
                            }
                        }
                    }
                }
                long long ans = (dp_next[0][0] + dp_next[0][n - 1] + dp_next[n - 1][0] + dp_next[n - 1][n - 1]) % M;
                s[q][n][k] = (s[q][n][k - 1] + ans) % M;

                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        dp[i][j] = dp_next[i][j];
                        dp_next[i][j] = 0;
                    }
                }
            }
            c[q][n] = berlekamp_massey(s[q][n]);
        }
    }
    cin >> t;
    while (t--) {
        long long n, k;
        cin >> n >> k;
        vector<long long> ans(2);
        for (int q = 0; q < 2; q++) {
            M = m[q];
            ans[q] = solve(c[q][2 * n], s[q][2 * n], k);
        }
        vector<pair<long long, long long>> v{{ans[0], m[0]}, {ans[1], m[1]}};
        cout << crt(v) << endl;
    }

    return 0;
}
