//https://cses.fi/problemset/task/3141/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll M = 1e9 + 7;

int main() {
    IOS;
    int n, k = 0;;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        k = max(k, 32 - __builtin_clz(a[i]));
    }
    vector<int> dp(1 << k, 0);
    for (int i = 0; i < n; i++) {
        dp[a[i]]++;
    }
    vector<ll> pw(n + 1, 0);
    pw[0] = 1;
    for (int i = 1; i <= n; i++) {
        pw[i] = pw[i - 1] * 2 % M;
    }

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < 1 << k; j++) {
            int c = (1 << i) & j;
            if (!c) {
                dp[j] = dp[j] + dp[j | (1 << i)];
            }
        }
    }

    vector<ll> ans(1 << k, 0);
    for (int j = 0; j < 1 << k; j++ ){
        ans[j] = pw[dp[j]] - 1;
    }

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < 1 << k; j++) {
            int c = (1 << i) & j;
            if (!c) {
                ans[j] = (ans[j] - ans[j | (1 << i)] + M) % M;
            }
        }
    }
    for (int j = 0; j < min(1 << k, n + 1); j++) {
        cout << ans[j] << " ";
    }
    for (int j = 1 << k; j <= n; j++) {
        cout << 0 << " ";
    }

    return 0;
}
