//https://www.codechef.com/START201A/problems/TUPLE_SLIMES
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;
const ll INF = 1e18;

ll a[N], b[N];
ll dp[N][N][3];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i] >> b[i];
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j + i < n; j++) {
                if (i == 0) {
                    dp[j][j][0] = a[j];
                    dp[j][j][1] = b[j];
                    dp[j][j][2] = a[j] + b[j];
                    continue;
                }
                dp[j][j + i][0] = INF;
                dp[j][j + i][1] = INF;
                dp[j][j + i][2] = -INF;
                for (int k = j; k < j + i; k++) {
                    dp[j][j + i][0] = min({dp[j][j + i][0], dp[j][k][0] + dp[k + 1][j + i][1], dp[k + 1][j + i][0] + dp[j][k][1]});
                    dp[j][j + i][1] = min({dp[j][j + i][1], dp[j][k][1] - dp[k + 1][j + i][2], dp[k + 1][j + i][1] - dp[j][k][2]});
                    dp[j][j + i][2] = max({dp[j][j + i][2], dp[j][k][2] - dp[k + 1][j + i][0], dp[k + 1][j + i][2] - dp[j][k][0]});
                }
            }
        }
        cout << dp[0][n - 1][2] << endl;
    }

    return 0;
}
