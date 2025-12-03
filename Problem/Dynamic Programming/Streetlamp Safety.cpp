//https://www.facebook.com/codingcompetitions/hacker-cup/2025/round-3/problems/B/my-submissions
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 6005;
const ll INF = 1e18;

int a[N];
int b[N];
int need[N][N];
ll dp[N][N];
ll suf[N][N];

int main() {
    IOS;
    freopen("248.in", "r", stdin);
    freopen("248.out", "w", stdout);
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        for (int i = 1; i <= n; i++) {
            cin >> b[i];
            b[i] = max(b[i], b[i - 1]);
        }
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                dp[i][j] = INF;
                suf[i][j] = INF;
            }
        }
        dp[0][0] = 0;
        suf[0][0] = 0;
        for (int l = 1; l <= n; l++) {
            int mx = 0;
            for (int r = l; r <= n; r++) {
                if (b[r] - (r - l) - 1 > 0) {
                    mx = max(mx, b[r]);
                }
                need[l][r] = mx;
            }
        }


        for (int i = 1; i <= n; i++) {
            for (int j = b[i]; j <= n; j++) {
                dp[i][j] = dp[i - 1][j];
            }
            ll s = 0;
            for (int j = i; j > 0; j--) {
                int sz = i - j + 1;
                s += a[j];
                dp[i][sz] = min(dp[i][sz], suf[j - 1][need[j][i]] + s);

            }
            suf[i][n] = dp[i][n];
            for (int j = n - 1; j >= 0; j--) {
                suf[i][j] = min(suf[i][j + 1], dp[i][j]);
            }
        }
        cout << "Case #" << tt << ": " << suf[n][0] << endl;
    }
    return 0;
}
