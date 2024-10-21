//https://www.codechef.com/problems/FIRSTSTRCHAR
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;

int dp[N][N][2];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        string a, b;
        cin >> a >> b;
        if (m > n || a[0] != b[0]) {
            cout << -1 << endl;
            continue;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                dp[i][j][0] = N * N;
                dp[i][j][1] = N * N;
            }
        }
        dp[0][0][1] = 0;
        for (int i = 1; i < n; i++) {
            dp[i][0][0] = 1;
            for (int j = 1; j < m; j++) {
                dp[i][j][0] = min(dp[i - 1][j][0], dp[i - 1][j][1] + 1);
                if (a[i] == b[j]) {
                    dp[i][j][1] = min(dp[i - 1][j - 1][0], dp[i - 1][j - 1][1]);
                }
            }
        }
        int ans = min(dp[n - 1][m - 1][0], dp[n - 1][m - 1][1]);
        if (ans > N) {
            cout << -1 << endl;
        } else {
            cout << ans << endl;
        }

    }
    return 0;
}
