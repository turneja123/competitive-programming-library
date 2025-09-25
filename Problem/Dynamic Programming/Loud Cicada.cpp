//https://atcoder.jp/contests/abc423/tasks/abc423_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 21;
const ll INF = (ll)1e18 + 1;

ll a[N];
ll dp[1 << N];

int main() {
    IOS;
    int n, m; ll y;
    cin >> n >> m >> y;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i < 1 << n; i++) {
        ll prod = 1;
        for (int j = 0; j < n; j++) {
            int c = i & (1 << j);
            if (c) {
                __int128 tmp = (__int128)prod * a[j] / __gcd(prod, a[j]);
                if (tmp >= INF) {
                    prod = INF;
                    break;
                }
                prod = tmp;
            }
        }
        dp[i] = y / prod;
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < 1 << n; j++) {
            int c = j & (1 << i);
            if (!c) {
                dp[j] -= dp[j ^ (1 << i)];
            }
        }
    }
    for (int j = 1; j < 1 << n; j++) {
        if (__builtin_popcount(j) == m) {
            ans += dp[j];
        }
    }
    cout << ans;


    return 0;
}
