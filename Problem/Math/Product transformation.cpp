//https://codeforces.com/contest/852/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int M = 1;

vector<ll> inv;
vector<ll> fact;
vector<ll> factinv;

ll binomial(ll n, ll k) {
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

int main() {
    IOS;
    ll n, m, a, q;
    cin >> n >> m >> a >> q;

    vector<ll> vals{a};
    ll cur = a;
    while (cur != 1) {
        cur = cur * a % q;
        vals.push_back(cur);
        M++;
    }

    inv.resize(M + 1);
    fact.resize(M + 1);
    factinv.resize(M + 1);
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i <= M; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    vector<ll> ans(n, 0);
    int s = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (m >= n - 1 - i) {
            s = (s + binomial(m, n - 1 - i)) % M;
        }
        ans[i] = vals[(s - 1 + M) % M];
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}
