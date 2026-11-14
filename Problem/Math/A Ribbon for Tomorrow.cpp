//https://codeforces.com/contest/2255/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const ll M = 998244353;

ll inv[N];
ll fact[N];
ll factinv[N];

ll binomial(ll n, ll k) {
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

ll stars(ll n, ll k) {
    return binomial(n + k - 1, n);
}

int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }

    int t;
    cin >> t;
    while (t--) {
        int m; string s;
        cin >> m >> s;
        int n[2] = {};
        int ct[2] = {};
        for (int i = 0; i < m; i++) {
            ct[s[i] - '0']++;
            if (i != 0 && s[i] != s[i - 1]) {
                n[s[i - 1] - '0']++;
            }
            if (i == m - 1) {
                n[s[i] - '0']++;
            }
        }
        ll ans = 1;
        for (int i = 0; i < 2; i++) {
            if (ct[i] == 0) {
                continue;
            }
            ans = ans * stars(ct[i] - n[i], n[i]) % M;
        }

        cout << ans << endl;
    }
    return 0;
}
