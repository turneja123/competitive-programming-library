//https://atcoder.jp/contests/abc282/tasks/abc282_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 105;
long long M;

int a[N];
long long dp[N][N][N][N];
long long pref[N][N][N];
long long col[N][N][N];

void preprocess(int n, int k) {
    pref[0][0][k] = dp[n - 1][0][0][k];
    col[0][0][k] = dp[n - 1][0][0][k];
    for (int i = 1; i < n; i++) {
        pref[0][i][k] = (pref[0][i - 1][k] + dp[n - 1][0][i][k]) % M;
        col[0][i][k] = dp[n - 1][0][i][k];
    }
    for (int i = 1; i < n; i++) {
        pref[i][0][k] = (pref[i - 1][0][k] + dp[n - 1][i][0][k]) % M;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            col[i][j][k] = (col[i - 1][j][k] + dp[n - 1][i][j][k]) % M;
            pref[i][j][k] = pref[i][j - 1][k] + col[i][j][k];
        }
    }
}

long long query(int y1, int x1, int y2, int x2, int k) {
    if (y1 > y2 || x1 > x2) {
        return 0;
    }
    return (pref[y2][x2][k] - (y1 == 0 ? 0 : pref[y1 - 1][x2][k]) - (x1 == 0 ? 0 : pref[y2][x1 - 1][k]) + (x1 == 0 || y1 == 0 ? 0 : pref[y1 - 1][x1 - 1][k]) + M * 4) % M;
}

int main() {
    IOS;
    int n, kk;
    cin >> n >> kk >> M;
    dp[0][0][0][0] = 1;
    preprocess(1, 0);
    for (int i = 1; i < n; i++) {
        for (int ja = 0; ja <= i; ja++) {
            for (int jb = 0; jb <= i; jb++) {
                for (int k = 0; k <= kk; k++) {
                    //> >
                    dp[i][ja][jb][k + 1] = (dp[i][ja][jb][k + 1] + query(0, 0, ja - 1, jb - 1, k)) % M;
                    //< <
                    dp[i][ja][jb][k + 1] = (dp[i][ja][jb][k + 1] + query(ja, jb, i - 1, i - 1, k)) % M;
                    //> <
                    dp[i][ja][jb][k] = (dp[i][ja][jb][k] + query(0, jb, ja - 1, i - 1, k)) % M;
                    //< >
                    dp[i][ja][jb][k] = (dp[i][ja][jb][k] + query(ja, 0, i - 1, jb - 1, k)) % M;
                }
            }
        }
        for (int k = 0; k <= kk; k++) {
            preprocess(i + 1, k);
        }
    }
    long long ans = 0;
    for (int ja = 0; ja < n; ja++) {
        for (int jb = 0; jb < n; jb++) {
            ans += dp[n - 1][ja][jb][kk];
        }
    }
    cout << ans % M;

    return 0;
}
