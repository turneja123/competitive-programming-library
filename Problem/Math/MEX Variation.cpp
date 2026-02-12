//https://www.codechef.com/START224A/problems/MXCHG
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
ll pw[N];

ll binomial(ll n, ll k) {
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1, pw[0] = 1;
    for (int i = 1; i < N; i++) {
        pw[i] = pw[i - 1] * 2 % M;
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> freq(n);
        vector<ll> prod(n + 1, 1);
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            freq[a]++;
        }
        ll ans = 0, ct = 1;
        for (int i = n - 1; i >= 0; i--) {
            prod[i] = prod[i + 1] * pw[freq[i]] % M;
            if (i != 0) {
                ans = (ans + prod[i] - 1 + M) % M;
                ans = (ans + (pw[freq[0]] - 1) * (prod[i + 1] - 1)) % M;
            }
        }
        int m = freq[1];
        vector<ll> ways_last(n + 1, 1);
        vector<ll> ways(n + 1, 0);
        for (int i = 2; i <= n; i++){
            m = min(m, freq[i - 1]);
            ways[0] = pw[freq[i - 1]];
            ways_last[0] = ways_last[0] * ways[0] % M;
            for (int j = 1; j <= m; j++) {
                ways[j] = (ways[j - 1] - binomial(freq[i - 1], j - 1) + M) % M;
                ways_last[j] = ways_last[j] * ways[j] % M;
                ans = (ans + (pw[freq[0]] - 1) * ways_last[j] % M * (i + j >= n ? 1 : prod[i + j])) % M;
            }
        }
        cout << ans << endl;
    }

    return 0;
}
