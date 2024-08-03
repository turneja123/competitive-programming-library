//https://www.spoj.com/problems/RANAGIC/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int S = 37;
const int N = 49;

long double dp[2][2][3][S][S][S * N];
long double fact[N * N];

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(9);
    fact[0] = 1;
    for (int i = 1; i < N * N; i++) {
        fact[i] = fact[i - 1] * i;
    }
    dp[0][0][0][0][0][1] = 1;
    dp[0][0][1][1][0][1] = 1;
    dp[0][0][2][0][1][1] = 1;
    for (int i = 2; i < S * N; i++) {
        for (int x = 0; x < S; x++) {
            for (int y = 0; y < S && x + y <= i; y++) {
                dp[0][0][0][x][y][i] = dp[0][0][0][x][y][i - 1] + dp[0][0][1][x][y][i - 1] + dp[0][0][2][x][y][i - 1];
                if (x != 0) {
                    dp[0][0][1][x][y][i] = dp[0][0][0][x - 1][y][i - 1] + dp[0][0][2][x - 1][y][i - 1];
                }
                if (y != 0) {
                    dp[0][0][2][x][y][i] = dp[0][0][0][x][y - 1][i - 1] + dp[0][0][1][x][y - 1][i - 1];
                }

                dp[0][1][0][x][y][i] = dp[0][1][0][x][y][i - 1] + dp[0][1][1][x][y][i - 1] + dp[0][1][2][x][y][i - 1];
                if (x != 0) {
                    dp[0][1][1][x][y][i] = dp[0][1][0][x - 1][y][i - 1] + dp[0][0][1][x - 1][y][i - 1] + dp[0][1][1][x - 1][y][i - 1] + dp[0][1][2][x - 1][y][i - 1];
                }
                if (y != 0) {
                    dp[0][1][2][x][y][i] = dp[0][1][0][x][y - 1][i - 1] + dp[0][1][1][x][y - 1][i - 1];
                }

                dp[1][0][0][x][y][i] = dp[1][0][0][x][y][i - 1] + dp[1][0][1][x][y][i - 1] + dp[1][0][2][x][y][i - 1];
                if (x != 0) {
                    dp[1][0][1][x][y][i] = dp[1][0][0][x - 1][y][i - 1] + dp[1][0][2][x - 1][y][i - 1];
                }
                if (y != 0) {
                    dp[1][0][2][x][y][i] = dp[1][0][0][x][y - 1][i - 1] + dp[0][0][2][x][y - 1][i - 1] + dp[1][0][2][x][y - 1][i - 1] + dp[1][0][1][x][y - 1][i - 1];
                }

                dp[1][1][0][x][y][i] = dp[1][1][0][x][y][i - 1] + dp[1][1][1][x][y][i - 1] + dp[1][1][2][x][y][i - 1];
                if (x != 0) {
                    dp[1][1][1][x][y][i] = dp[1][1][0][x - 1][y][i - 1] + dp[1][0][1][x - 1][y][i - 1] + dp[1][1][1][x - 1][y][i - 1] + dp[1][1][2][x - 1][y][i - 1];
                }
                if (y != 0) {
                    dp[1][1][2][x][y][i] = dp[1][1][0][x][y - 1][i - 1] + dp[0][1][2][x][y - 1][i - 1] + dp[1][1][2][x][y - 1][i - 1] + dp[1][1][1][x][y - 1][i - 1];
                }
            }
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int s, c;
        cin >> s >> c;
        long double valid = (dp[1][1][0][s][s][s * c] + dp[1][1][1][s][s][s * c] + dp[1][1][2][s][s][s * c]) * fact[s] * fact[s] * fact[s * c - 2 * s];
        cout << valid / fact[s * c]  << endl;
    }

    return 0;
}
