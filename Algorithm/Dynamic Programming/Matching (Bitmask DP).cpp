//https://atcoder.jp/contests/dp/tasks/dp_o
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 22;
const long long M = 1e9 + 7;

int a[N][N];
long long dp[N][1 << N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    for (int j = 0; j < n; j++) {
        if (a[0][j] == 1) {
            dp[0][1 << j] = 1;
        }
    }
    for (int i = 1; i < n; i++) {
        for (int mask = 1; mask < (1 << n); mask++) {
            if (__builtin_popcount(mask) != (i + 1)) {
                continue;
            }
            for (int j = 0; j < n; j++) {
                int c = mask & (1 << j);
                if (!c || !a[i][j]) {
                    continue;
                }
                dp[i][mask] = (dp[i][mask] + dp[i - 1][mask ^ (1 << j)]) % M;
            }
        }
    }
    cout << dp[n - 1][(1 << n) - 1] << endl;

    return 0;
}
