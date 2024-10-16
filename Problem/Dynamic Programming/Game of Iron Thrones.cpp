//https://www.spoj.com/problems/GOIT/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;

long double dp[N][N];

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(2);
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        dp[0][0] = 1.0;
        for (int i = 1; i <= n; i++) {
            long double c;
            cin >> c >> c >> c >> c >> c >> c;
            dp[i][0] = dp[i - 1][0] * (1.0 - c);
            for (int j = 1; j <= i; j++) {
                dp[i][j] = dp[i - 1][j] * (1.0 - c) + dp[i - 1][j - 1] * c;
            }
        }
        long double ans = 0.0;
        for (int j = k; j <= n; j++) {
            ans += dp[n][j];
        }
        cout << ans << endl;
    }

    return 0;
}
