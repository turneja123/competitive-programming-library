//https://codeforces.com/contest/575/problem/H
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e6 + 5;
const ll M = 1e9 + 7;

ll inv[N];
ll fact[N];
ll factinv[N];

ll binomial(ll n, ll k) {
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    int n;
    cin >> n;
    ll ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = (ans + binomial(n + i + 1, i + 1)) % M;
    }
    cout << ans;

    return 0;
}
