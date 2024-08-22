//https://atcoder.jp/contests/abc322/tasks/abc322_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 105;
const int K = 50005;
const long long INF = 1e18;

vector<int> a[N];
vector<int> pos[K];

int pw[10];
int cost[N];
long long dp[N][K];

int main() {
    IOS;
    int n, k, p;
    cin >> n >> k >> p;
    p++;
    for (int i = 1; i <= n; i++) {
        cin >> cost[i];
        a[i].resize(k);
        for (int j = 0; j < k; j++) {
            cin >> a[i][j];
        }
    }
    pw[0] = 1;
    for (int i = 1; i <= k; i++) {
        pw[i] = pw[i - 1] * p;
    }
    for (int i = 0; i < pw[k]; i++) {
        pos[i].resize(k);
        int j = 0, mask = i;
        while (mask > 0) {
            pos[i][j++] = mask % p;
            mask /= p;
        }
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < pw[k]; j++) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < pw[k]; j++) {
            if (dp[i - 1][j] == INF) {
                continue;
            }
            dp[i][j] = min(dp[i][j], dp[i - 1][j]);
            int mask = 0;
            for (int d = 0; d < k; d++) {
                mask += min(p - 1, pos[j][d] + a[i][d]) * pw[d];
            }
            dp[i][mask] = min(dp[i][mask], dp[i - 1][j] + cost[i]);
        }
    }
    if (dp[n][pw[k] - 1] == INF) {
        cout << -1;
    } else {
        cout << dp[n][pw[k] - 1];
    }
    return 0;
}
