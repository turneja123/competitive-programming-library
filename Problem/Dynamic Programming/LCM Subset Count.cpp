//https://ocpc2026w.eolymp.space/en/compete/ig3v7lohgt0vd43nv48bk2lb4o/problem/7
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll unsigned long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const ll M = 998244353;

bool is_prime[N];
vector<int> primes;

ll dp[N];

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
    for (int i = 1; i < N; i++) {
        is_prime[i] = 1;
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
        ll n, k;
        cin >> n >> k;
        vector<ll> f;
        for (int p : primes) {
            ll e = 1;
            while (k % p == 0) {
                e *= p;
                k /= p;
            }
            if (e > 1) {
                f.push_back(e);
            }
        }
        int m = f.size();
        for (int j = 0; j < 1 << m; j++) {
            ll prod = 1;
            for (int i = 0; i < m; i++) {
                int c = (1 << i) & j;
                if (c) {
                    prod *= f[i];
                }
            }
            dp[j] = n / prod;
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < 1 << m; j++) {
                int c = (1 << i) & j;
                if (!c) {
                    dp[j] -= dp[j ^ (1 << i)];
                }
            }
        }
        dp[0] = modPow(2, dp[0]);
        for (int j = 1; j < 1 << m; j++) {
            dp[j] = modPow(2, dp[j]);
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < 1 << m; j++) {
                int c = (1 << i) & j;
                if (c) {
                    dp[j] = dp[j] * dp[j ^ (1 << i)] % M;
                }
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < 1 << m; j++) {
                int c = (1 << i) & j;
                if (c) {
                    dp[j] = (dp[j] - dp[j ^ (1 << i)] + M) % M;
                }
            }
        }
        cout << dp[(1 << m) - 1] << endl;

    }

    return 0;
}
