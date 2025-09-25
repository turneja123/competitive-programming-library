//https://atcoder.jp/contests/abc424/tasks/abc424_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;
const ll INF = 1e18;

int sum[N];
vector<int> items[N];

int a[N];
ll dp[N][N * N];
ll dp_nx[N][N * N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1, greater<int>());
    for (int i = n; i > 0; i--) {
        sum[i] = a[i] + sum[i + 1];
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N * N; j++) {
            dp[i][j] = -INF;
        }
    }
    dp[0][0] = 0;
    for (int i = 0; i < m; i++) {
        int b, c;
        cin >> b >> c;
        if (b == 0) {
            dp[0][0] += c;
        } else {
            items[b].push_back(c);
        }
    }

    for (int k = n; k > 0; k--) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N * N; j++) {
                int cost = i + j;
                if (i + j <= sum[k]) {
                    dp_nx[i][i + j] = max(dp_nx[i][i + j], dp[i][j]);
                }
            }
        }
        for (int add : items[k]) {
            for (int i = N - 2; i >= 0; i--) {
                for (int j = N * N - 2; j >= 0; j--) {
                    if (dp_nx[i][j] == -INF) {
                        continue;
                    }
                    if (j + 1 <= sum[k]) {
                        dp_nx[i + 1][j + 1] = max(dp_nx[i + 1][j + 1], dp_nx[i][j] + add);
                    }
                }
            }
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N * N; j++) {
                dp[i][j] = dp_nx[i][j];
                dp_nx[i][j] = -INF;
            }
        }
    }
    ll ans = -INF;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N * N; j++) {
            ans = max(ans, dp[i][j]);
        }
    }
    cout << ans;

    return 0;
}
