//solution for https://codeforces.com/contest/1475/problem/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int a[n];
        bool b[N] = { };
        int dp[N] = { };
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a, a + n);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= sqrt(a[i]); j++) {
                if (a[i] % j == 0) {
                    if (b[j]) {
                        dp[a[i]] = max(dp[a[i]], dp[j] + 1);
                    }
                    if (a[i] / j != j && b[a[i] / j]) {
                        dp[a[i]] = max(dp[a[i]], dp[a[i] / j] + 1);
                    }
                }
            }
            dp[a[i]] = max(dp[a[i]], 1);
            b[a[i]] = true;
            ans = max(ans, dp[a[i]]);
        }
        cout << n - ans << endl;
    }
    return 0;
}
