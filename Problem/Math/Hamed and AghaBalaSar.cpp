//https://codeforces.com/contest/2127/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const ll M = 1e9 + 7;

long long inv[N];
long long fact[N];
long long factinv[N];

long long binomial(long long n, long long k) {
    if (k > n || min(n, k) < 0) {
        return 0;
    }
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

ll f1(ll n, ll m, ll x) {
    if (n < 0) {
        return 0;
    }
    if (m < 0) {
        return 0;
    }
    if (n == 0) {
        return 1;
    }
    ll ans = 0;
    for (ll j = 0; j <= m / (x + 1); ++j) {
        ll add = binomial(n, j) * binomial(m - j * (x + 1) + n, n) % M;
        if (j % 2 == 1) {
            ans = (ans - add + M) % M;
        } else {
            ans = (ans + add) % M;
        }
    }
    return ans;
}

ll f2(ll n, ll m, ll x) {
    if (n <= 0) {
        return 0;
    }
    if (m < 0) {
        return 0;
    }
    ll ans = 0;
    for (ll j = 0; j <= m / (x + 1); ++j) {
        ll y = m - j * (x + 1);
        ll add = ((m - y) * binomial(y + n, n) + n * binomial(y + n, n + 1)) % M;
        add = add * binomial(n, j) % M;

        if (j % 2 == 1) {
            ans = (ans - add + M) % M;
        } else {
            ans = (ans + add) % M;
        }
    }
    return ans;
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
        ll n, m;
        cin >> n >> m;
        ll ans = 0;
        for (ll i = 1; i <= m; i++) {
            ll l = max((ll)0, m - (n - 1) * i);
            ll r = min(i - 1, m - i);
            if (l <= r) {
                ll x = (f1(n - 2, m - i - l, i) - f1(n - 2, m - i - r - 1, i) + M) % M;
                ll y = (f2(n - 2, m - i - l, i) - f2(n - 2, m - i - r - 1, i) + M) % M;
                ans = (ans + (2 * i - m + M) * x + y) % M;
            }
            if (m - 2 * i >= 0) {
                r = min(i - 1, m - 2 * i);
                if (l <= r) {
                    ll x = (f1(n - 3, m - 2 * i - l, i) - f1(n - 3, m - 2 * i - r - 1, i) + M) % M;
                    ll y = (f2(n - 3, m - 2 * i - l, i) - f2(n - 3, m - 2 * i - r - 1, i) + M) % M;
                    ans = (ans + ((3 * i - m + M) * x + y) % M * (n - 2)) % M;
                }
            }

        }
        cout << ans << endl;
    }
	return 0;
}
