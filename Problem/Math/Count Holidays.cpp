//https://atcoder.jp/contests/abc456/tasks/abc456_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll M = 998244353;

ll inv[N];
ll fact[N];
ll factinv[N];
ll pw[N];
ll ans[N];

ll modPow(ll a, ll y) {
    ll res = 1;
    while (y > 0) {
        if (y % 2 != 0) {
            res = res * a % M;
        }
        y /= 2;
        a = a * a % M;
    }
    return res;
}


ll binomial(ll n, ll k) {
    if (n < 0 || k > n || k < 0) {
        return 0;
    }
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}


int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1, pw[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
        pw[i] = pw[i - 1] * 2 % M;
    }
    int n;
    cin >> n;
    string s;
    cin >> s;
    for (int i = 0; i <= n; i++) {
        ans[i] = 1;
    }
    map<int, int> mp;
    int ct = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'x') {
            if (ct) {
                mp[ct]++;
            }
            ct = 0;
        } else {
            ct++;
        }
    }
    if (ct) {
        mp[ct]++;
    }

    for (auto [m, p] : mp) {
        vector<ll> g(m + 2, 0), f(m + 2, 0);
        for (int i = 1; i <= m + 1; i++) {
            g[i] = pw[m];
            for (int j = 1; i * j <= m; j++) {
                if (j % 2 == 0) {
                    g[i] = (g[i] + binomial(m - i * j, j) * pw[m - i * j - j] + binomial(m - i * j, j - 1) * pw[m - i * j - j + 1]) % M;
                } else {
                    g[i] = (g[i] - binomial(m - i * j, j) * pw[m - i * j - j] % M - binomial(m - i * j, j - 1) * pw[m - i * j - j + 1] % M + 2 * M) % M;
                }
            }
        }
        ll s = 0;
        for (int i = 0; i <= m; i++) {
            f[i] = (g[i + 1] - g[i] + M) % M;
            s = (s + f[i]) % M;
            ans[i] = ans[i] * modPow(s, p) % M;
        }
        s = modPow(s, p);
        for (int i = m + 1; i <= n; i++) {
            ans[i] = ans[i] * s % M;
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << (ans[i] - ans[i - 1] + M) % M << endl;
    }

    return 0;
}
