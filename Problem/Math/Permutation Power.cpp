//https://ocpc2026w.eolymp.space/en/compete/r1t2e978517l1a1e5a39p463hs/problem/5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 32000;
const int F = 5e5 + 5;
const ll M = 1e9 + 7;

vector<int> primes;
vector<int> divs;
ll inv[F];
ll fact[F];
ll factinv[F];
bool is_prime[N];

void get_divs(int i, int cur, vector<pair<int, int>> &f) {
    if (i == f.size()) {
        divs.push_back(cur);
        return;
    }
    for (int j = 0; j <= f[i].second; j++) {
        get_divs(i + 1, cur, f);
        cur *= f[i].first;
    }
    return;
}

int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < F; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    for (int i = 1; i < N; i++) {
        is_prime[i] = true;
    }
    is_prime[1] = false;
    for (int i = 2; i < N; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = 2 * i; j < N; j += i) {
                is_prime[j] = false;
            }
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n), vis(n), lengths(n + 1, 0);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
        }
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                int u = i, ct = 0;
                while (!vis[u]) {
                    ct++;
                    vis[u] = 1;
                    u = a[u];
                }
                lengths[ct]++;
            }
        }
        int tmp = k;
        vector<pair<int, int>> f;
        for (int p : primes) {
            int e = 0;
            while (tmp % p == 0) {
                tmp /= p;
                e++;
            }
            if (e) {
                f.push_back({p, e});
            }
        }
        if (tmp > 1) {
            f.push_back({tmp, 1});
        }
        get_divs(0, 1, f);
        ll ans = 1;
        for (int i = 1; i <= n; i++) {
            if (!lengths[i]) {
                continue;
            }
            vector<ll> pw(lengths[i] + 1, 0);
            vector<ll> dp(lengths[i] + 1, 0);
            pw[0] = 1;
            dp[0] = 1;
            for (int j = 1; j <= lengths[i]; j++) {
                pw[j] = pw[j - 1] * i % M;
            }

            for (int j = 1; j <= lengths[i]; j++) {
                for (int d : divs) {
                    if (d <= lengths[i] && j >= d && __gcd(i, k / d) == 1) {
                        dp[j] = (dp[j] + dp[j - d] * pw[d - 1] % M * inv[j]) % M;
                    }
                }
            }
            ans = ans * dp[lengths[i]] % M * fact[lengths[i]] % M;
        }
        cout << ans << endl;
        divs.clear();
    }



    return 0;
}
