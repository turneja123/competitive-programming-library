//solution for https://cses.fi/problemset/task/1158
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;

int dp[N][100 * N];
int wt[N];
int val[N];

int main() {
    IOS;
    int n, x;
    cin >> n >> x;
    for (int i = 0; i < n; i++) {
        cin >> wt[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= x; j++) {
            dp[i][j] = dp[i - 1][j];
            if (wt[i - 1] <= j) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - wt[i - 1]] + val[i - 1]);
            }
        }
    }
    cout << dp[n][x];
    return 0;
}
