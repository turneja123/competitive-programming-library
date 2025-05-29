//https://codeforces.com/contest/2066/problem/D2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e4 + 5;
const int C = 105;
const long long M = 1e9 + 7;

int a[N];
long long inv[N];
long long fact[N];
long long factinv[N];
long long dp[C][N];
int ct[N];
int last[N];
int pref[N];

long long binomial(long long n, long long k) {
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

long long calc(int i, int n, int c, int m, int tot, int all) {
    if (m < c) {
        return 0;
    }
    if (i == n) {
        return c == m && ct[i] <= c;
    }
    if (dp[i][all] != -1) {
        return dp[i][all];
    }
    if (last[i] - (tot - m) > c) {
        return 0;
    }

    dp[i][all] = 0;
    for (int j = ct[i]; j <= c; j++) {
        if (pref[c + (tot - m)] - all >= j - ct[i]) {
            dp[i][all] = (dp[i][all] + calc(i + 1, n, c, m - j, tot, all + j - ct[i]) * binomial(pref[c + (tot - m)] - all, j - ct[i])) % M;
        }
    }
    return dp[i][all];
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
        int n, c, m;
        cin >> n >> c >> m;
        for (int i = 0; i <= n; i++) {
            ct[i] = 0;
            last[i] = -1;
        }
        for (int i = 0; i < m; i++) {
            cin >> a[i];
            ct[a[i]]++;
            last[a[i]] = i + 1;
            pref[i + 1] = pref[i] + (a[i] == 0);
        }
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                dp[i][j] = -1;
            }
        }
        cout << calc(1, n, c, m, m, 0) << endl;

    }

    return 0;
}
