//https://cses.fi/problemset/task/1075/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;
const long long M = 1e9 + 7;

long long dp[N][N][5]; // 0 - new comp on far left/far right, 1 - new comp otherwise, 2 - used to merge 2 comps, 3 - added on far left/far right, 4 - added otherwise

int main() {
    IOS;
    int n;
    cin >> n;
    dp[1][1][0] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            dp[i][j + 1][0] = (dp[i - 1][j][0] + dp[i - 1][j][1] + dp[i - 1][j][2] + dp[i - 1][j][3] + dp[i - 1][j][4]) * 2 % M;
            dp[i][j + 1][1] = (dp[i - 1][j][0] + dp[i - 1][j][1] + dp[i - 1][j][2] + dp[i - 1][j][3] + dp[i - 1][j][4]) * (j - 1) % M;
            dp[i][j - 1][2] = (dp[i - 1][j][0] * (j - 2) + dp[i - 1][j][1] * (j - 3) + dp[i - 1][j][2] * (j - 1) + dp[i - 1][j][3] * (j - 1) + dp[i - 1][j][4] * (j - 2)) % M;
            dp[i][j][3] = (dp[i - 1][j][0] + dp[i - 1][j][1] * 2 + dp[i - 1][j][2] * 2 + dp[i - 1][j][3] + dp[i - 1][j][4] * 2) % M;
            dp[i][j][4] = (dp[i - 1][j][0] * (2 * j - 3) + dp[i - 1][j][1] * (2 * j - 4) + dp[i - 1][j][2] * (2 * j - 2) + dp[i - 1][j][3] * (2 * j - 2) + dp[i - 1][j][4] * (2 * j - 3)) % M;
        }
    }
    cout << (dp[n][1][0] + dp[n][1][1] + dp[n][1][2] + dp[n][1][3] + dp[n][1][4]) % M;

    return 0;
}
