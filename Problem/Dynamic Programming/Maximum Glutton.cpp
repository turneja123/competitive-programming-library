//https://atcoder.jp/contests/abc364/tasks/abc364_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

typedef long long ll;

const int N = 85;
const int M = 10005;
const int INF = 1e9;

int dp[N][M];
int a[N];
int b[N];

int main() {
    IOS;
    int n, x, y;
    cin >> n >> x >> y;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    for (int k = 0; k <= n; k++) {
        for (int j = 0; j <= x; j++) {
            dp[k][j] = INF;
        }
    }
    dp[0][0] = 0;
    dp[1][a[0]] = b[0];
    for (int i = 1; i < n; i++) {
        for (int k = i + 1; k > 0; k--) {
            for (int j = a[i]; j <= x; j++) {
                if (dp[k - 1][j - a[i]] != INF) {
                    dp[k][j] = min(dp[k][j], dp[k - 1][j - a[i]] + b[i]);
                }
            }
        }
    }
    int ans = 0;
    for (int k = 1; k <= n; k++) {
        for (int j = 0; j <= x; j++) {
            if (dp[k][j] <= y) {
                ans = k;
            }
        }
    }
    cout << min(n, ans + 1);

    return 0;
}
