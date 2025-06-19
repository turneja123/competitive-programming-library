//https://codeforces.com/contest/1920/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2505;
const long long M = 998244353;

long long dp[N][N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                dp[i][j] = 0;
            }
        }
        for (int j = 1; j <= n; j++) {
            dp[0][j] = 1;
        }

        long long ans = 0;
        for (int i = 0; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dp[i][j] == 0) {
                    continue;
                }
                for (int k = 1; i + j * k <= n && j + k - 1 <= m; k++) {
                    dp[i + j * k][k] = (dp[i + j * k][k] + dp[i][j]) % M;
                }
                for (int k = 0; k <= n; k++) {
                    if (i + j * (k + 1) > n || j + k > m) {
                        break;
                    }
                    if (i + j * (k + 1) == n) {
                        ans = (ans + dp[i][j]) % M;
                    }
                }
            }
        }
        cout << ans << endl;
    }

    return 0;
}
