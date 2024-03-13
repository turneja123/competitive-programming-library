//https://atcoder.jp/contests/abc336/tasks/abc336_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int E = 15;
const int N = 9 * E + 1;

long long dp[N][N][N][10][2]; //broj cifara, suma, modulo, ostatak, most significant cifra
long long dp_prev[N][N][N][10][2];

int main() {
    long long a, b, c = 1;
    cin >> a;
    long long ans = min(9ll, a);
    for (int i = 0; i < 10; i++) {
        for (int m = 1; m < N; m++) {
            if (a % 10 >= i) {
                dp_prev[i][m][i % m][i][0] = 1;
            } else {
                dp_prev[i][m][i % m][i][1] = 1;
            }
        }
    }
    long long d = 1;
    for (int n = 1; n < E; n++) {
        d *= 10;
        a /= 10;
        if (a > 0) {
            c++;
        }
        for (int sum = 0; sum <= (n + 1) * 9; sum++) {
            for (int m = 1; m < N; m++) {
                for (int t = 0; t < m; t++) {
                    for (int cif = 0; cif < 10 && sum >= cif; cif++) {
                        dp[sum][m][t][cif][0] = 0;
                        dp[sum][m][t][cif][1] = 0;
                        for (int j = 0; j < 10; j++) {
                            if (a % 10 > cif) {
                                dp[sum][m][t][cif][0] += dp_prev[sum - cif][m][(((t - d * (long long)cif) % m) + m) % m][j][0];
                                dp[sum][m][t][cif][0] += dp_prev[sum - cif][m][(((t - d * (long long)cif) % m) + m) % m][j][1];
                            } else if (a % 10 == cif) {
                                dp[sum][m][t][cif][0] += dp_prev[sum - cif][m][(((t - d * (long long)cif) % m) + m) % m][j][0];
                                dp[sum][m][t][cif][1] += dp_prev[sum - cif][m][(((t - d * (long long)cif) % m) + m) % m][j][1];
                            } else {
                                dp[sum][m][t][cif][1] += dp_prev[sum - cif][m][(((t - d * (long long)cif) % m) + m) % m][j][0] + dp_prev[sum - cif][m][(((t - d * (long long)cif) % m) + m) % m][j][1];

                            }
                        }
                    }
                }
            }
        }
        for (int sum = 1; sum < N; sum++) {
            for (int cif = 1; cif < 10; cif++) {
                ans += dp[sum][sum][0][cif][0];
                if (a > 9) {
                    ans += dp[sum][sum][0][cif][1];
                }
            }
        }
        for (int sum = 0; sum <= (n + 1) * 9; sum++) {
            for (int m = 1; m < N; m++) {
                for (int t = 0; t < m; t++) {
                    for (int cif = 0; cif < 10 && sum >= cif; cif++) {
                        dp_prev[sum][m][t][cif][0] = dp[sum][m][t][cif][0];
                        dp_prev[sum][m][t][cif][1] = dp[sum][m][t][cif][1];
                    }
                }
            }
        }
    }
    cout << ans << endl;

    return 0;
}
