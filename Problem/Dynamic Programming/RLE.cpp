//https://atcoder.jp/contests/abc249/tasks/abc249_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;

int dp[N][N][26];
int sum[N][N];

int main() {
    IOS;
    int n; long long M;
    cin >> n >> M;
    for (int d = 0; d < 26; d++) {
        dp[1][2][d] = 1;
    }
    sum[1][2] = 26;
    sum[0][0] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= n; j++) {
            for (int d = 0; d < 26; d++) {
                dp[i][j][d] += dp[i - 1][j][d];
                if (dp[i][j][d] >= M) {
                    dp[i][j][d] -= M;
                }

                if (i >= 10) {
                    dp[i][j][d] -= sum[i - 10][j - 2] - dp[i - 10][j - 2][d];
                    if (dp[i][j][d] < 0) {
                        dp[i][j][d] += M;
                    }
                    if (dp[i][j][d] > M) {
                        dp[i][j][d] -= M;
                    }
                    dp[i][j + 1][d] += sum[i - 10][j - 2] - dp[i - 10][j - 2][d];
                    if (dp[i][j + 1][d] >= M) {
                        dp[i][j + 1][d] -= M;
                    }
                    if (dp[i][j + 1][d] < 0) {
                        dp[i][j + 1][d] += M;
                    }
                }

                if (i >= 100) {
                    dp[i][j + 1][d] -= sum[i - 100][j - 2] - dp[i - 100][j - 2][d];
                    if (dp[i][j + 1][d] < 0) {
                        dp[i][j + 1][d] += M;
                    }
                    if (dp[i][j + 1][d] > M) {
                        dp[i][j + 1][d] -= M;
                    }
                    dp[i][j + 2][d] += sum[i - 100][j - 2] - dp[i - 100][j - 2][d];
                    if (dp[i][j + 2][d] >= M) {
                        dp[i][j + 2][d] -= M;
                    }
                    if (dp[i][j + 2][d] < 0) {
                        dp[i][j + 2][d] += M;
                    }
                }

                if (i >= 1000) {
                    dp[i][j + 2][d] -= sum[i - 1000][j - 2] - dp[i - 1000][j - 2][d];
                    if (dp[i][j + 2][d] < 0) {
                        dp[i][j + 2][d] += M;
                    }
                    if (dp[i][j + 2][d] > M) {
                        dp[i][j + 2][d] -= M;
                    }
                    dp[i][j + 3][d] += sum[i - 1000][j - 2] - dp[i - 1000][j - 2][d];
                    if (dp[i][j + 3][d] >= M) {
                        dp[i][j + 3][d] -= M;
                    }
                    if (dp[i][j + 3][d] < 0) {
                        dp[i][j + 3][d] += M;
                    }
                }

                if (j >= 2) {
                    dp[i][j][d] += sum[i - 1][j - 2] - dp[i - 1][j - 2][d];
                    if (dp[i][j][d] >= M) {
                        dp[i][j][d] -= M;
                    }
                    if (dp[i][j][d] < 0) {
                        dp[i][j][d] += M;
                    }
                }
                sum[i][j] += dp[i][j][d];
                if (sum[i][j] >= M) {
                    sum[i][j] -= M;
                }
            }
        }
    }
    long long ans = 0;
    for (int j = 2; j < n; j++) {
        ans += sum[n][j];
    }
    cout << ans % M;
    return 0;
}
