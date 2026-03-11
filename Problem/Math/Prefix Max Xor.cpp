//https://www.codechef.com/problems/PMXXOR
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
        int n;
        cin >> n;
        map<int, int> mp;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            mp[a]++;
        }
        vector<ll> p(n, 0);
        vector<int> vals;
        vector<int> f;
        for (auto [_, d] : mp) {
            vals.push_back(_);
            f.push_back(d);
        }
        reverse(vals.begin(), vals.end());
        reverse(f.begin(), f.end());
        int m = 0;
        for (int i = 0; i < f.size(); i++) {
            for (int j = 1; j <= f[i]; j++) {
                p[i] = (1 - p[i] + M) * j % M * inv[m + j] % M;
            }
            m += f[i];
        }
        ll ans = 0;
        for (int i = 0; i < 30; i++) {
            ll dp[2] = {};
            dp[0] = 1;
            for (int j = 0; j < f.size(); j++) {
                int c = (1 << i) & vals[j];
                if (!c) {
                    continue;
                }
                ll dp_nx[2] = {};
                dp_nx[0] = ((1 - p[j] + M) * dp[0] + p[j] * dp[1]) % M;
                dp_nx[1] = ((1 - p[j] + M) * dp[1] + p[j] * dp[0]) % M;
                dp[0] = dp_nx[0];
                dp[1] = dp_nx[1];
            }
            ans = (ans + dp[1] * (1 << i)) % M;
        }
        cout << ans << endl;


    }
    return 0;
}
