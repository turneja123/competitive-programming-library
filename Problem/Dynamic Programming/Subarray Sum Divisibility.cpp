//https://atcoder.jp/contests/abc419/tasks/abc419_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;
const int INF = 1e9;

int a[N];
int cost[N][N];
int dp[N][N];

int main() {
    IOS;
    int n, m, l;
    cin >> n >> m >> l;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int k = 0; k < l; k++) {
        for (int i = k; i < n; i += l) {
            for (int j = 0; j < m; j++) {
                int wt;
                if (a[i] <= j) {
                    wt = j - a[i];
                } else {
                    wt = m - (a[i] - j);
                }
                cost[k][j] += wt;
            }
        }
    }
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < m; j++) {
            dp[i][j] = INF;
        }
    }
    for (int i = 0; i < l; i++) {
        if (i == 0) {
            for (int j = 0; j < m; j++) {
                dp[0][j] = cost[0][j];
            }
        } else {
            for (int prev = 0; prev < m; prev++) {
                for (int add = 0; add < m; add++) {
                    dp[i][(prev + add) % m] = min(dp[i][(prev + add) % m], dp[i - 1][prev] + cost[i][add]);
                }
            }
        }
    }
    cout << dp[l - 1][0];
    return 0;
}
