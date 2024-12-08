//https://cses.fi/problemset/task/1726/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;

long double ans[8][8];
long double dp[N][8][8];
int dir[8][8];

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(6);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            ans[i][j] = 1.0;
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (abs(dx) + abs(dy) == 1 && i + dx >= 0 && i + dx < 8 && j + dy >= 0 && j + dy < 8) {
                        dir[i][j]++;
                    }
                }
            }
        }
    }
    int n;
    cin >> n;
    for (int x0 = 0; x0 < 8; x0++) {
        for (int y0 = 0; y0 < 8; y0++) {
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    dp[0][i][j] = 0.0;
                }
            }
            dp[0][x0][y0] = 1.0;
            for (int k = 1; k <= n; k++) {
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {
                        dp[k][i][j] = 0;
                        for (int dx = -1; dx <= 1; dx++) {
                            for (int dy = -1; dy <= 1; dy++) {
                                if (abs(dx) + abs(dy) == 1 && i + dx >= 0 && i + dx < 8 && j + dy >= 0 && j + dy < 8) {
                                    dp[k][i][j] += dp[k - 1][i + dx][j + dy] / (long double)dir[i + dx][j + dy];
                                }
                            }
                        }
                    }
                }
            }
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    ans[i][j] *= ((long double)1.0 - dp[n][i][j]);
                }
            }
        }
    }
    long double sum = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            sum += ans[i][j];
        }
    }
    cout << sum;



    return 0;
}
