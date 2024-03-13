//https://usaco.org/index.php?page=viewproblem2&cpid=647
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 250;
const int INF = 1e9;

int a[N];
int dp[N][N];

int main() {
    //IOS;
    freopen("248.in", "r", stdin);
    int n, ans = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j + i < n; j++) {
            if (i == 0) {
                dp[j][j] = a[j];
                ans = max(ans, a[j]);
                continue;
            }
            dp[j][j + i] = 0;
            for (int k = j; k < j + i; k++) {
                if (dp[j][k] != 0 && dp[j][k] == dp[k + 1][j + i]) {
                    dp[j][j + i] = max(dp[j][j + i], dp[j][k] + 1);
                    ans = max(ans, dp[j][j + i]);
                }
            }
        }
    }
    freopen("248.out", "w", stdout);
    cout << ans << endl;
    return 0;
}
