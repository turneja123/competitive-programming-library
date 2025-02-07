//https://codeforces.com/contest/2049/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 205;
const long long INF = 1e18;

long long a[N][N];
long long dp[N][N];
long long pref[N][N];

long long get_pref(int n, int m, int l, int r) {
    if (l <= r) {
        long long ans = pref[n][r] - (l == 0 ? 0 : pref[n][l - 1]);
        return ans;
    }
    long long ans = pref[n][m - 1] - pref[n][l - 1] + pref[n][r];
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m, c;
        cin >> n >> m >> c;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> a[i][j];
                dp[i][j] = INF;
                pref[i][j] = (j == 0 ? a[i][j] : pref[i][j - 1] + a[i][j]);
            }
        }
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < m; k++) {
                dp[0][j] = min(dp[0][j], get_pref(0, m, (0 + k) % m, (j + k) % m) + (long long)k * c);
            }
        }
        for (int i = 1; i < n; i++) {
            for (int k = 0; k < m; k++) {
                long long mn = INF, sum = 0;
                for (int j = 0; j < m; j++) {
                    mn = min(mn, dp[i - 1][j] - sum);
                    sum += a[i][(j + k) % m];
                    dp[i][j] = min(dp[i][j], mn + sum + (long long)k * c);
                }
            }
        }
        cout << dp[n - 1][m - 1] << endl;
    }
    return 0;
}
