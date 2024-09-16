//https://dmoj.ca/problem/coci20c3p4
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 10;
const int M = 1000;
const int INF = 1e9;

char trans[M][N];
char a[N][M];
int dp[N][M][1 << N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            trans[i][j] = s[j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[j][i] = trans[i][j];
        }
    }
    swap(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int mask = 0; mask < 1 << n; mask++) {
                dp[i][j][mask] = INF;
            }
        }
    }
    if (a[0][0] == '.') {
        dp[0][0][(1 << n) - 1] = 0;
    } else {
        dp[0][0][(1 << n) - 1] = 1;
        dp[0][0][(1 << n) - 2] = 0;
    }

    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            if (i == 0 && j == 0) {
                continue;
            }
            for (int mask = 0; mask < 1 << n; mask++) {
                if (i == 0) {
                    if (a[i][j] == '.') {
                        if ((mask & (1 << i))) {
                            dp[i][j][mask] = dp[n - 1][j - 1][mask];
                        }
                    } else {
                        if ((mask & (1 << i))) {
                            dp[i][j][mask] = dp[n - 1][j - 1][mask ^ (1 << i)] + 1;
                            dp[i][j][mask] = min(dp[i][j][mask], dp[n - 1][j - 1][mask] + 1);
                        } else {
                            dp[i][j][mask] = min(dp[n - 1][j - 1][mask], dp[n - 1][j - 1][mask | (1 << i)]);
                        }

                    }

                } else {
                    if (a[i][j] == '.') {
                        if ((mask & (1 << i))) {
                            dp[i][j][mask] = dp[i - 1][j][mask];
                        }
                    } else {

                        if ((mask & (1 << i))) {
                            dp[i][j][mask] = dp[i - 1][j][mask ^ (1 << i)] + 1;
                            dp[i][j][mask] = min(dp[i][j][mask], dp[i - 1][j][mask] + 1);
                            for (int p = i - 1; p >= 0; p--) {
                                dp[i][j][mask] = min(dp[i][j][mask], dp[p][j][mask] + 1);
                                if (!(mask & (1 << p))) {
                                    break;
                                }
                                if (a[p][j] == '.') {
                                    break;
                                }
                                if (p == 0 && j > 0) {
                                    dp[i][j][mask] = min(dp[i][j][mask], dp[n - 1][j - 1][mask] + 1);
                                } else if (p == 0 && j == 0) {
                                    dp[i][j][mask] = 1;
                                }
                            }

                        } else {
                            dp[i][j][mask] = min(dp[i - 1][j][mask], dp[i - 1][j][mask | (1 << i)]);
                        }
                    }
                }
            }
        }
    }
    cout << dp[n - 1][m - 1][(1 << n) - 1];
    return 0;
}
