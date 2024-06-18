//https://atcoder.jp/contests/abc358/tasks/abc358_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 51;
const int K = N * N * 2;

long long dp[N][N][K];
int a[N][N];

vector<pair<int, int>> moves{{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {0, 0}};

int main() {
    IOS;
    int n, m, k;
    cin >> n >> m >> k;
    int si, sj, p = k;
    cin >> si >> sj;
    si--, sj--;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            for (int k = 0; k < K; k++) {
                dp[i][j][k] = -1;
            }
        }
    }
    dp[si][sj][0] = 0;
    for (int k = 1; k < K; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                long long mx = -1;
                for (int d = 0; d < 5; d++) {
                    int dx = moves[d].first, dy = moves[d].second;
                    if (i + dx >= 0 && i + dx < n && j + dy >= 0 && j + dy < m) {
                        mx = max(mx, dp[i + dx][j + dy][k - 1]);
                    }
                }
                if (mx != -1) {
                    dp[i][j][k] = mx + a[i][j];
                }
            }
        }
    }
    long long ans = -1;
    if (p >= K) {
        p = K - 1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (dp[i][j][p] > ans) {
                ans = dp[i][j][p];
            }
        }
    }
    if (k < K) {
        cout << ans;
    } else {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans = max(ans, dp[i][j][p] + (long long)a[i][j] * (k - K + 1));
            }
        }
        cout << ans;
    }
    return 0;
}
