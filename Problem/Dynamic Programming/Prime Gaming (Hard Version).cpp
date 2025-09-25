//https://codeforces.com/contest/2140/problem/E2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 21;
const ll M = 1e9 + 7;

int can[N];
int dp[1 << N][2];
ll ct[1 << N];
ll pw[N][1 << N];

int get(int x, int k) {
    if (x == 0) {
        return 0;
    }
    int msb = 31 - __builtin_clz(x), p = msb - k;
    int high = x >> (p + 1), low  = x & ((1 << p) - 1);
    return (high << p) | low;
}

int calc(int mask, int n, int flag) {
    if (n == 1) {
        return dp[mask][flag] = 1 + (mask % 2);
    }
    if (dp[mask][flag] != 0) {
        return dp[mask][flag];
    }
    dp[mask][flag] = (flag == 0 ? 1 : 2);
    for (int i = 1; i <= n; i++) {
        if (can[i]) {
            int go = get(mask, i);
            if (flag == 0) {
                dp[mask][flag] = max(dp[mask][flag], calc(go, n - 1, 1));
            } else {
                dp[mask][flag] = min(dp[mask][flag], calc(go, n - 1, 0));
            }
        }
    }
    return dp[mask][flag];
}

int main() {
    IOS;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 1 << N; j++) {
            if (i == 0) {
                pw[i][j] = 1;
            } else {
                pw[i][j] = pw[i - 1][j] * j % M;
            }
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        for (int i = 1; i <= n; i++) {
            can[i] = 0;
        }
        for (int i = 0; i < k; i++) {
            int j;
            cin >> j;
            can[j] = 1;
        }
        if (m == 1) {
            cout << 1 << endl;
            continue;
        }
        for (int i = 0; i < 1 << (n + 1); i++) {
            dp[i][0] = 0;
            dp[i][1] = 0;
        }
        for (int i = 0; i < 1 << n; i++) {
            int ans = calc((1 << n) + i, n, 0);
            if (ans == 2) {
                ct[__builtin_popcount(i)]++;
            }
        }
        ll ans = 0;
        for (int i = 0; i <= n; i++) {
            ll s = 0;
            for (int j = 0; j <= m - 1; j++) {
                s = (s + pw[i][m - j] * pw[n - i][j]) % M;
            }
            ans = (ans + ct[i] * s) % M;
        }
        for (int i = 0; i < 1 << n; i++) {
            ct[i] = 0;
        }
        cout << ans << endl;
    }
    return 0;
}
