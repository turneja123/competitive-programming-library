//https://cses.fi/problemset/task/1744/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;
const int INF = 1e9;

int dp[N][N];

int calc(int n, int m) {
    if (n == m) {
        return 0;
    }
    if (dp[n][m] != INF) {
        return dp[n][m];
    }
    int ans = INF;
    for (int i = 1; i < n; i++) {
        ans = min(ans, calc(n - i, m) + calc(i, m) + 1);
    }
    for (int i = 1; i < m; i++) {
        ans = min(ans, calc(n, m - i) + calc(n, i) + 1);
    }
    return dp[n][m] = ans;
}


int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = INF;
        }
    }
    cout << calc(n, m);



    return 0;
}
