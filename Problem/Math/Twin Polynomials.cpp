//https://codeforces.com/contest/2159/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;
const ll M = 1e9 + 7;

ll dp[N];
long long inv[N];
long long fact[N];
long long factinv[N];

long long binomial(long long n, long long k) {
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
    dp[0] = 1, dp[1] = 1;
    for (int i = 2; i < N; i++) {
        dp[i] = (dp[i - 1] + dp[i - 2] * (i - 1)) % M;
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n + 1);
        for (int i = 0; i <= n; i++) {
            cin >> a[i];
        }
        ll ans = 1;
        for (int i = 1; i <= n; i++) {
            if (a[i] > 0) {
                if (a[i] > n) {
                    ans = 0;
                    continue;
                }
                if (a[a[i]] != -1 && a[a[i]] != i) {
                    ans = 0;
                }
                a[a[i]] = i;
            }
        }
        int m = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i] == -1) {
                m++;
            }
        }
        if (ans == 0) {
            cout << 0 << endl;
        } else {
            ans = 0;
            for (int i = 0; i <= m; i++) {
                ans = (ans + binomial(m, i) * dp[m - i]) % M;
            }
            if (a[n] == -1) {
                for (int i = 0; i <= m - 1; i++) {
                    ans = (ans - binomial(m - 1, i) * dp[m - 1 - i] % M + M) % M;
                }
            }
            cout << ans << endl;
        }
    }
    return 0;
}
