//https://codeforces.com/contest/1423/problem/J
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 62;
const ll M = 1e9 + 7;

ll dp[2][8];

inline ll mod(ll x) {
    if (x >= 4 * M) x -= 4 * M;
    if (x >= 2 * M) x -= 2 * M;
    if (x >= M) x -= M;
    return x;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        if (n == 1) {
            cout << 1 << endl;
            continue;
        }
        int bit = n & 1;
        n >>= 1;

        for (int add = bit; add < 8; add += 2) {
            dp[0][add >> 1]++;
        }
        int m = 1;
        while (n > 0) {
            int j = m % 2;
            bit = n & 1;
            n >>= 1;
            for (int mask = 0; mask < 8; mask++) {
                int x = dp[j ^ 1][mask];
                int z = ((bit ^ (mask & 1)) + mask) >> 1;
                dp[j][z] += x;
                dp[j][z + 1] += x;
                dp[j][z + 2] += x;
                dp[j][z + 3] += x;
            }

            for (int mask = 0; mask < 8; mask++) {
                dp[j][mask] = mod(dp[j][mask]);
                dp[j ^ 1][mask] = 0;
            }
            m++;
        }

        cout << dp[(m % 2) ^ 1][0] << endl;
        for (int mask = 0; mask < 8; mask++) {
            dp[0][mask] = 0;
            dp[1][mask] = 0;
        }
    }

    return 0;
}
