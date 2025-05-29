//https://www.codechef.com/problems/ANTISM
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long INF = 1e18;

long long dp[2][2][N];
long long pref[2][2][N];
long long a[N];
int b[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n; long long x;
        cin >> n >> x;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        for (int dx = 0; dx < 2; dx++) {
            for (int dy = 0; dy < 2; dy++) {
                for (int i = 0; i < n; i++) {
                    dp[dx][dy][i] = -INF;
                    pref[dx][dy][i] = -INF;
                }
            }
        }
        dp[0][b[0]][0] = a[0]; //has space, has increasable, index
        pref[0][b[0]][0] = a[0];
        for (int i = 1; i < n; i++) {
            dp[0][b[i]][i] = a[i];
            for (int dx = 0; dx < 2; dx++) {
                for (int dy = 0; dy < 2; dy++) {
                    dp[dx][dy | b[i]][i] = max(dp[dx][dy | b[i]][i], dp[dx][dy][i - 1] + a[i]);
                    if (i > 1) {
                        dp[1][dy | b[i]][i] = max(dp[1][dy | b[i]][i], pref[dx][dy][i - 2] + a[i]);
                    }
                }
            }
            for (int dx = 0; dx < 2; dx++) {
                for (int dy = 0; dy < 2; dy++) {
                    pref[dx][dy][i] = max(pref[dx][dy][i - 1], dp[dx][dy][i]);
                }
            }
        }
        if (pref[1][0][n - 1] >= x) {
            cout << 0 << endl;
        } else {
            long long ans = max(0ll, x - pref[1][1][n - 1]);
            cout << ans << endl;
        }
    }
    return 0;
}
