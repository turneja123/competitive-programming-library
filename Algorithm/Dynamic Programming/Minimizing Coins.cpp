//solution for https://cses.fi/problemset/task/1634/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int INF = 1e9;

int dp[N];
int coins[N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }
    for (int i = 1; i <= m; i++) {
        dp[i] = INF;
        for (int c = 0; c < n; c++) {
            if (i - coins[c] >= 0 && dp[i] > dp[i - coins[c]] + 1) {
                dp[i] = dp[i - coins[c]] + 1;
            }
        }
    }
    if (dp[m] != INF) {
        cout << dp[m];
    } else {
        cout << -1;
    }
    return 0;
}
