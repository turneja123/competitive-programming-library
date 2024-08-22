//https://vjudge.net/problem/Aizu-ALDS1_10_B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 405;
const long long INF = 1e18;

long long a[N], b[N];
long long dp[N][N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j + i < n; j++) {
            if (i == 0) {
                dp[j][j] = 0;
                continue;
            }
            dp[j][j + i] = INF;
            for (int k = j; k < j + i; k++) {
                dp[j][j + i] = min(dp[j][j + i], dp[j][k] + dp[k + 1][j + i] + a[j] * b[j + i] * b[k]);
            }
        }
    }
    cout << dp[0][n - 1] << endl;
    return 0;
}
