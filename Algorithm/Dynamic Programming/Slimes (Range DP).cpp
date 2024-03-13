//https://atcoder.jp/contests/dp/tasks/dp_n
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 405;
const long long INF = 1e18;

long long a[N];
long long dp[N][N];
long long cost[N][N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j + i < n; j++) {
            if (i == 0) {
                dp[j][j] = a[j];
                cost[j][j] = 0;
                continue;
            }
            dp[j][j + i] = INF;
            for (int k = j; k < j + i; k++) {
                if (dp[j][j + i] > dp[j][k] + dp[k + 1][j + i] || (dp[j][j + i] >= dp[j][k] + dp[k + 1][j + i] && cost[j][j + i] > dp[j][j + i] + cost[j][k] + cost[k + 1][j + i])) {
                    dp[j][j + i] = dp[j][k] + dp[k + 1][j + i];
                    cost[j][j + i] = dp[j][j + i] + cost[j][k] + cost[k + 1][j + i];
                }
            }
        }
    }
    cout << cost[0][n - 1] << endl;
    return 0;
}
