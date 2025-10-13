//https://codeforces.com/contest/2153/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll INF = 1e18;

int a[N];
ll dp[N];

ll calc(int i, int n) {
    for (; i < n; i++) {
        if (i - 2 >= 0) {
            dp[i] = min(dp[i], dp[i - 2] + abs(a[i - 1] - a[i]));
        }
        if (i - 3 >= 0) {
            dp[i] = min(dp[i], dp[i - 3] + max({a[i], a[i - 1], a[i - 2]}) - min({a[i], a[i - 1], a[i - 2]}));
        }
    }
    return dp[n - 1];
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        //a[0] = a[n - 1]
        for (int i = 0; i < n; i++) {
            dp[i] = INF;
        }
        dp[0] = abs(a[0] - a[n - 1]);
        ll ans = INF;
        ans = min(ans, calc(1, n - 1));
        //a[0] = a[n - 2] = a[n - 1]
        for (int i = 0; i < n; i++) {
            dp[i] = INF;
        }
        dp[0] = max({a[0], a[n - 2], a[n - 1]}) - min({a[0], a[n - 2], a[n - 1]});
        ans = min(ans, calc(1, n - 2));
        //a[0] = a[1] = a[n - 1]
        for (int i = 0; i < n; i++) {
            dp[i] = INF;
        }
        dp[1] = max({a[0], a[1], a[n - 1]}) - min({a[0], a[1], a[n - 1]});
        ans = min(ans, calc(2, n - 1));
        for (int i = 0; i < n; i++) {
            dp[i] = INF;
        }
        for (int i = 0; i < n; i++) {
            if (i - 2 >= -1) {
                dp[i] = min(dp[i], (i - 2 == -1 ? 0 : dp[i - 2]) + abs(a[i - 1] - a[i]));
            }
            if (i - 3 >= -1) {
                dp[i] = min(dp[i], (i - 3 == -1 ? 0 : dp[i - 3]) + max({a[i], a[i - 1], a[i - 2]}) - min({a[i], a[i - 1], a[i - 2]}));
            }
        }
        ans = min(ans, dp[n - 1]);
        cout << ans << endl;
    }
    return 0;
}
