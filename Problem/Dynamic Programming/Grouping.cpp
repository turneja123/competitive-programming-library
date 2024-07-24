//https://atcoder.jp/contests/dp/tasks/dp_u
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int K = 16;
const int N = 1 << K;

long long a[K][K];

long long dp[N];

int main() {
    IOS;
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            cin >> a[i][j];
        }
    }

    for (int j = 0; j < (1 << k); j++) {
        for (int x = 0; x < k; x++) {
            for (int y = x + 1; y < k; y++) {
                int c1 = j & (1 << x), c2 = j & (1 << y);
                if (c1 > 0 && c2 > 0) {
                    dp[j] += a[x][y];
                }
            }
        }
        for (int mask = j; mask > 0; mask = (mask - 1) & j) {
            dp[j] = max(dp[j], dp[mask] + dp[j ^ mask]);
        }
    }
    cout << dp[(1 << k) - 1];

    return 0;
}
