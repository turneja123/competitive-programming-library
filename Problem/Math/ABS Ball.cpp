//https://atcoder.jp/contests/arc212/tasks/arc212_c
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e7 + 5;
const ll M = 998244353;

ll inv[N];
ll fact[N];
ll factinv[N];
ll pw[N];

ll binomial(ll n, ll k) {
    if (n < 0 || k < 0 || k > n) {
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
    int n, m;
    cin >> n >> m;
    ll ans = 0;
    for (int i = 0; i <= n - m; i++) {
        ans = (ans + binomial(n - i + 2 * m - 1, 3 * m - 1) * binomial(m - 1 + i, m - 1) % M * pw[m] % M * (i % 2 == 0 ? 1 : (M - 1))) % M;
    }
    cout << ans;
    return 0;
}
