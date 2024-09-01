//https://judge.beecrowd.com/en/problems/view/1353
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const long long M = 1e9 + 9;

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
    if (k < 0) {
        return 0;
    }
    if (k < n) {
        return s[k] % M;
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

const int K = 11;
const int N = 125;

long long dp[K][N][N];

long long ncr[5];

vector<long long> s[11];
vector<long long> c[11];

int main() {
    IOS;
    ncr[1] = 4, ncr[2] = 6, ncr[3] = 4, ncr[4] = 1;
    dp[0][0][0] = 1;
    for (int add = 1; add < N; add++) {
        for (int i = 1; i < N; i++) {
            for (int j = 1; j < K; j++) {
                for (int k = 1; k <= min(4, j); k++) {
                    if (i >= add * k) {
                        dp[j][add][i] = (dp[j][add][i] + dp[j - k][add - 1][i - add * k] * ncr[k]) % M;
                    }
                }
                dp[j][add][i] = (dp[j][add][i] + dp[j][add - 1][i]) % M;
            }
        }
        dp[0][add][0] = 1;

    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i < N; i++) {
            dp[k][i][i] = (dp[k][i][i] + dp[k - 1][i][i]) % M;
            s[k].push_back(dp[k][i][i]);
        }
        c[k] = berlekamp_massey(s[k]);
    }
    long long n, k;
    cin >> n >> k;
    while (n != 0) {
        cout << solve(c[k], s[k], n - 1) << endl;
        cin >> n >> k;
    }

    return 0;
}
