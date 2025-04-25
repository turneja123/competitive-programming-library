//https://dmoj.ca/problem/joi16op3
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;
const int K = 1005;

const long long M = 1e9 + 7;

int a[N];

long long dp[N][N][K][3];

int main() {
    IOS;
    int n, l;
    cin >> n >> l;
    int mn = K;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mn = min(mn, a[i]);
    }
    for (int i = 0; i < n; i++) {
        a[i] -= mn;
    }
    if (n == 1) {
        cout << 1;
        return 0;
    }
    sort(a, a + n);
    if (a[n - 1] > l) {
        cout << 0;
        return 0;
    }
    dp[0][1][a[1] - a[0]][1] = 2;
    if (2 * (a[1] - a[0]) <= l) {
        dp[0][1][2 * (a[1] - a[0])][0] = 1;
    }

    for (int i = 1; i < n; i++) {
        int cost = (i == n - 1 ? K : a[i + 1] - a[i]);
        for (int j = 1; j <= i; j++) {
            for (int k = 1; k <= l; k++) {
                if (k + 2 * j * cost <= l) {
                    dp[i][j][k + 2 * j * cost][0] = (dp[i][j][k + 2 * j * cost][0] + dp[i - 1][j][k][0] * (2 * j)) % M;
                }
                if (k + (2 * j + 2) * cost <= l) {
                    dp[i][j + 1][k + (2 * j + 2) * cost][0] = (dp[i][j + 1][k + (2 * j + 2) * cost][0] + dp[i - 1][j][k][0] * (j + 1)) % M;
                }
                if (k + (2 * j - 2) * cost <= l) {
                    dp[i][j - 1][k + (2 * j - 2) * cost][0] = (dp[i][j - 1][k + (2 * j - 2) * cost][0] + dp[i - 1][j][k][0] * (j - 1)) % M;
                }

                if (k + (2 * j - 1) * cost <= l) {
                    dp[i][j][k + (2 * j - 1) * cost][1] = (dp[i][j][k + (2 * j - 1) * cost][1] + dp[i - 1][j][k][0] * 2) % M;
                }
                if (k + (2 * j + 1) * cost <= l) {
                    dp[i][j + 1][k + (2 * j + 1) * cost][1] = (dp[i][j + 1][k + (2 * j + 1) * cost][1] + dp[i - 1][j][k][0] * 2) % M;
                }

                if (k + (2 * j - 1) * cost <= l) {
                    dp[i][j][k + (2 * j - 1) * cost][1] = (dp[i][j][k + (2 * j - 1) * cost][1] + dp[i - 1][j][k][1] * (2 * j - 1)) % M;
                }
                if (k + (2 * j + 1) * cost <= l) {
                    dp[i][j + 1][k + (2 * j + 1) * cost][1] = (dp[i][j + 1][k + (2 * j + 1) * cost][1] + dp[i - 1][j][k][1] * j) % M;
                }
                if (k + (2 * j - 3) * cost <= l) {
                    dp[i][j - 1][k + (2 * j - 3) * cost][1] = (dp[i][j - 1][k + (2 * j - 3) * cost][1] + dp[i - 1][j][k][1] * (j - 1)) % M;
                }

                if (k + (2 * j - 2) * cost <= l) {
                    dp[i][j][k + (2 * j - 2) * cost][2] = (dp[i][j][k + (2 * j - 2) * cost][2] + dp[i - 1][j][k][1]) % M;
                }
                if (k + 2 * j * cost <= l) {
                    dp[i][j + 1][k + 2 * j * cost][2] = (dp[i][j + 1][k + 2 * j * cost][2] + dp[i - 1][j][k][1]) % M;
                }

                if (k + (2 * j - 2) * cost <= l) {
                    dp[i][j][k + (2 * j - 2) * cost][2] = (dp[i][j][k + (2 * j - 2) * cost][2] + dp[i - 1][j][k][2] * (2 * j - 2)) % M;
                }
                if (k + 2 * j * cost <= l) {
                    dp[i][j + 1][k + 2 * j * cost][2] = (dp[i][j + 1][k + 2 * j * cost][2] + dp[i - 1][j][k][2] * (j - 1)) % M;
                }
                if (k + (2 * j - 4) * cost <= l) {
                    dp[i][j - 1][k + (2 * j - 4) * cost][2] = (dp[i][j - 1][k + (2 * j - 4) * cost][2] + dp[i - 1][j][k][2] * (j - 1)) % M;
                }
            }
        }
    }
    long long ans = 0;
    for (int k = 1; k <= l; k++) {
        ans = (ans + dp[n - 1][1][k][2]) % M;
    }
    cout << ans;
    return 0;
}
