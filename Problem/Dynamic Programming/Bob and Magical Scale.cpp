//https://www.spoj.com/problems/MGCSCLS/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 50;
const int M = 25;
const int W = 100;
const int S = N * M * W;

int dp[M][S + 1][2];
int a[M][N][2];
int pref[M][N][2];

int main() {
    IOS;
    int n, l, r;
    cin >> n >> l >> r;
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j][0];
            pref[i][j][0] = ((j == 0) ? a[i][j][0] : pref[i][j - 1][0] + a[i][j][0]);
        }
    }
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j][1];
            pref[i][j][1] = ((j == 0) ? a[i][j][1] : pref[i][j - 1][1] + a[i][j][1]);
        }
    }
    int Z = S / 2;
    for (int i = 0; i < l; i++) {
        for (int w = 0; w <= S; w++) {
            dp[i][w][0] = -1;
        }
    }
    for (int i = 0; i < r; i++) {
        for (int w = 0; w <= S; w++) {
            dp[i][w][1] = -1;
        }
    }
    dp[0][Z][0] = 0;
    for (int j = 0; j < n; j++) {
        dp[0][Z + pref[0][j][0]][0] = j + 1;
    }
    for (int i = 1; i < l; i++) {
        for (int w = 0; w <= S; w++) {
            dp[i][w][0] = dp[i - 1][w][0];
        }
        for (int j = 0; j < n; j++) {
            for (int w = 0; w <= S; w++) {
                int w_prev = w - pref[i][j][0];
                if (w_prev < 0 || w_prev > S) {
                    continue;
                }
                if (dp[i - 1][w_prev][0] != -1) {
                    dp[i][w][0] = max(dp[i][w][0], dp[i - 1][w_prev][0] + j + 1);
                }
            }
        }
    }
    dp[0][Z][1] = 0;
    for (int j = 0; j < n; j++) {
        dp[0][Z + pref[0][j][1]][1] = j + 1;
    }
    for (int i = 1; i < r; i++) {
        for (int w = 0; w <= S; w++) {
            dp[i][w][1] = dp[i - 1][w][1];
        }
        for (int j = 0; j < n; j++) {
            for (int w = 0; w <= S; w++) {
                int w_prev = w - pref[i][j][1];
                if (w_prev < 0 || w_prev > S) {
                    continue;
                }
                if (dp[i - 1][w_prev][1] != -1) {
                    dp[i][w][1] = max(dp[i][w][1], dp[i - 1][w_prev][1] + j + 1);
                }
            }
        }
    }
    int ans = n * (l + r);
    for (int w = 0; w <= S; w++) {
        if (dp[l - 1][w][0] != -1 && dp[r - 1][w][1] != -1) {
            ans = min(ans, n * l - dp[l - 1][w][0] + n * r - dp[r - 1][w][1]);
        }
    }
    cout << ans;
    return 0;
}
