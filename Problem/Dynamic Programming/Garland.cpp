//https://codeforces.com/contest/1287/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;
const int INF = 1e9;

int a[N];
int dp[N][N][2];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        for (int j = 0; j < n; j++) {
            dp[i][j][0] = INF;
            dp[i][j][1] = INF;
        }
    }
    if (a[0] == 0 || a[0] % 2 == 0) {
        dp[0][0][0] = 0;
    }
    if (a[0] == 0 || a[0] % 2 == 1) {
        dp[0][1][1] = 0;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < 2; k++) {
                if (a[i] == 0 || a[i] % 2 == 0) {
                    dp[i][j][0] = min(dp[i][j][0], dp[i - 1][j][k] + (k == 1));
                }
                if (a[i] == 0 || a[i] % 2 == 1) {
                    dp[i][j + 1][1] = min(dp[i][j + 1][1], dp[i - 1][j][k] + (k == 0));
                }
            }
        }
    }
    cout << min(dp[n - 1][(n + 1) / 2][0], dp[n - 1][(n + 1) / 2][1]);

    return 0;
}
