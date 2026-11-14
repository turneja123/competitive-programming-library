//https://codeforces.com/contest/717/problem/A
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll M = 1e9 + 7;

vector<ll> mul(int n, vector<ll> &a, vector<ll> &b, vector<ll> &tr) {
    vector<ll> res(n * 2 + 1, 0);
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

ll solve(vector<ll> &c, vector<ll> &s, ll k) {
    int n = c.size();
    if (n == 0) {
        return 0;
    }
    if (k < n) {
        return s[k];
    }
    vector<ll> x(n + 1), a(x);
    x[0] = 1, a[1] = 1;
    for (++k; k; k /= 2) {
        if (k % 2) {
            x = mul(n, x, a, c);
        }
        a = mul(n, a, a, c);
    }
    ll res = 0;
    for (int i = 0; i < n; i++) {
        res = (res + x[i + 1] * s[i]) % M;
    }
    return res;
}

ll modInverse(ll a, ll m) {
    ll res = 1;
    ll y = m - 2;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % m;
        }
        y /= 2;
        a = (a * a) % m;
    }
    return res;
}

vector<ll> berlekamp_massey(vector<ll> s) {
    int n = s.size(), l = 0, m = 0;
    vector<ll> c(n), b(n), t(n);
    c[0] = 1, b[0] = 1;
    ll d = 1;
    for (int i = 0; i < n; i++) {
        m++;
        ll d_next = s[i];
        for (int j = 1; j <= l; j++) {
            d_next = (d_next + (c[j] * s[i - j]) % M) % M;
        }
        if (d_next == 0) {
            continue;
        }
        t = c;
        ll coef = (d_next * modInverse(d, M)) % M;
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

const int N = 1610;

ll inv[N];
ll fact[N];
ll factinv[N];

ll binomial(ll n, ll k) {
    if (k > n) {
        return 0;
    }
    ll num = 1, denom = factinv[k];
    for (int i = n; i > n - k; i--) {
        num = num * i % M;
    }
    return num * denom % M;
}


int main() {
    IOS;
    int k; ll l, r;
    cin >> k >> l >> r;
    vector<ll> f(N);
    f[0] = 0, fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
        f[i] = (i == 1 ? 1 : f[i - 1] + f[i - 2]) % M;
    }
    vector<ll> s(N - 2);
    for (int i = 0; i < N - 2; i++) {
        s[i] = (i == 0 ? 0 : s[i - 1] + binomial(f[i + 2], k)) % M;
    }
    vector<ll> c = berlekamp_massey(s);
    cout << (solve(c, s, r) - solve(c, s, l - 1) + M) % M << endl;

    return 0;
}
