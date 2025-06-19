//https://atcoder.jp/contests/abc410/tasks/abc410_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;

int dp[N][N];


int main() {
    IOS;
    int n, h, m;
    cin >> n >> h >> m;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= h; j++) {
            dp[i][j] = -1;
        }
    }
    dp[0][h] = m;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        for (int j = a; j <= h; j++) {
            dp[i][j - a] = max(dp[i][j - a], dp[i - 1][j]);
        }
        for (int j = 0; j <= h; j++) {
            dp[i][j] = max(dp[i][j], dp[i - 1][j] - b);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= h; j++) {
            if (dp[i][j] >= 0) {
                ans = i;
            }
        }
    }
    cout << ans;
    return 0;
}
