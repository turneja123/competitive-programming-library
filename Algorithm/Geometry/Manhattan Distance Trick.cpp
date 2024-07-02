//https://www.spoj.com/problems/DISTANCE/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int K = 10;
const int INF = 2e9;

int a[N][K];

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            cin >> a[i][j];
        }
    }
    int ans = -INF;
    for (int mask = 1 << (k - 1); mask < (1 << k); mask++) {
        int mx = -INF, mn = INF;
        for (int i = 0; i < n; i++) {
            int cur = 0;
            for (int j = 0; j < k; j++) {
                int c = mask & (1 << j);
                if (c != 0) {
                    cur += a[i][j];
                } else {
                    cur -= a[i][j];
                }
            }
            mx = max(mx, cur);
            mn = min(mn, cur);
        }
        ans = max(ans, mx - mn);
    }
    cout << ans;
    return 0;
}
