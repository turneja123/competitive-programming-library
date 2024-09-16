//https://www.spoj.com/problems/PBOARD/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 10;
const int K = 1000;
const long long M = 10007;

long long dp[N][K][1 << N];

long long modInverse(long long a, long long m) {
    long long res = 1;
    long long y = m - 2;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % m;
        }
        y /= 2;
        a = (a * a) % m;
    }
    return res;
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
        long long coef = (d_next * modInverse(d, M)) % M;
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
    int n, m;
    //cin >> n >> m;
    n = 2, m = 15;
    dp[0][0][(1 << n) - 1] = 1;
    dp[0][0][(1 << n) - 2] = 1;
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            if (i == 0 && j == 0) {
                continue;
            }
            for (int mask = 0; mask < 1 << n; mask++) {
                if (i == 0) {
                    dp[i][j][mask] = dp[n - 1][j - 1][mask | (1 << i)];
                } else {
                    dp[i][j][mask] = dp[i - 1][j][mask | (1 << i)];
                    if ((mask & (1 << i)) && (mask & (1 << i - 1))) {
                        dp[i][j][mask] += dp[i - 1][j][mask ^ (1 << i - 1)];
                    }
                    if (j > 0) {
                        if (j == 1) {
                            if (i == 1 && mask == ((1 << n) - 1)) {
                                dp[i][j][mask] += 2;
                            }
                        } else {
                            if (mask == ((1 << n) - 1)) {
                                dp[i][j][mask] += 2 * dp[i][j - 2][mask];
                            }
                        }
                    }
                }
                dp[i][j][mask] %= M;
            }
        }
    }
    vector<long long> s{1};
    for (int i = 1; i < m; i++) {
        long long cur = 2 * dp[n - 1][i - 1][(1 << n) - 1];
        for (int j = 1; j < i; j++) {
            cur += dp[n - 1][j - 1][(1 << n) - 1] * dp[n - 1][i - j - 1][(1 << n) - 1];
        }
        s.push_back(cur % M);
    }

    vector<long long> c = berlekamp_massey(s);
    long long t;
    cin >> t;
    while (t != -1) {
        cout << solve(c, s, t) << endl;
        cin >> t;
    }

    return 0;
}
