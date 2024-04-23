//https://www.spoj.com/problems/FIBOSUM2/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 1000000007;

const int N = 6;
const int F = 5e5;
const int K = (1 << 15) + 5;

long long fib[F];
vector<long long> c[K];

vector<long long> mul(int n, vector<long long> &a, vector<long long> &b, vector<long long> &tr) {
    vector<long long> res(n * 2 + 1, 0);
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            res[i + j] += a[i] * b[j];
        }
    }
    for (int i = 2 * n; i > n; --i) {
        res[i] %= M;
        for (int j = 0; j < n; j++) {
            res[i - 1 - j] += res[i] * tr[j];
        }
    }
    res.resize(n + 1);
    res[0] %= M, res[1] %= M, res[2] %= M, res[3] %= M;
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
        return s[k];
    }
    vector<long long> x(n + 1), a(x);
    x[0] = -1, a[1] = 1;
    for (++k; k; k /= 2) {
        if (k % 2) {
            if (x[0] == -1) {
                x = a;
            } else {
                x = mul(n, x, a, c);
            }
        }
        if (k > 1) {
            a = mul(n, a, a, c);
        }
    }
    long long res = 0;
    for (int i = 0; i < n; i++) {
        res += x[i + 1] * s[i];
    }
    return res % M;
}

long long modPow(long long a, long long y, long long m) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % m;
        }
        y /= 2;
        a = (a * a) % m;
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
            d_next += c[j] * s[i - j];
        }
        d_next %= M;
        if (d_next == 0) {
            continue;
        }
        t = c;
        long long coef = (d_next * modPow(d, M - 2, M)) % M;
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
    fib[0] = 0, fib[1] = 1;
    for (int i = 2; i < F; i++) {
        fib[i] = (fib[i - 1] + fib[i - 2]) % M;
    }
    for (int p = 1; p < K; p++) {
        vector<long long> s(6);
        s[0] = fib[p];
        for (int k = 1; k < 6; k++) {
            s[k] = (s[k - 1] + fib[(k + 1) * p]) % M;
        }
        c[p] = berlekamp_massey(s);
    }
    int t;
    cin >> t;
    for (int p = 1; p <= t; p++) {
        long long m, k, n;
        cin >> m >> k >> n;
        long long s1 = fib[k + m], s2 = (s1 + fib[2 * k + m]) % M, s3 = (s2 + fib[3 * k + m]) % M;
        vector<long long> s{s1, s2, s3};
        cout << solve(c[k], s, n - 1) << endl;
    }

    return 0;
}
