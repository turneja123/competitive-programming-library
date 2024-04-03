//https://cses.fi/problemset/task/1639/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e3 + 5;
const int INF = 1e9;

int dp[N][N];

int main() {
    IOS;
    string a, b;
    cin >> a >> b;
    if (a.size() > b.size()) {
        swap(a, b);
    }
    int n = a.size(), m = b.size();
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = INF;
        }
    }
    for (int i = 1; i <= n; i++) {
        dp[i][0] = i;
    }
    for (int j = 1; j <= m; j++) {
        dp[0][j] = j;
    }
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (dp[i - 1][j - 1] != INF) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + (a[i - 1] != b[j - 1]));
            }
            if (dp[i][j - 1] != INF) {
                dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
            }
            if (dp[i - 1][j] != INF) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
            }
        }
    }
    cout << dp[n][m];

    return 0;
}
