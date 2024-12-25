//https://atcoder.jp/contests/abc385/tasks/abc385_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const long double INF = 1e20;

int x[N], h[N];

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(16);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> h[i];
    }
    long double l = 0, r = 1ll << 60; long double ans = -1;
    for (int k = 0; k < 500; k++) {
        long double mid = (l + r) / 2;
        bool can = true;
        long double s = -INF;
        for (int i = 0; i < n && can; i++) {
            long double mx = mid + s * (long double)x[i];
            if (mx >= h[i]) {
                can = false;
            }
            long double cur = ((long double)h[i] - mid) / (long double)x[i];
            if (cur > s) {
                s = cur;
            }
        }
        if (can) {
            r = mid;
        } else {
            ans = mid;
            l = mid;
        }
    }
    if (ans < 0) {
        cout << -1;
    } else {
        cout << ans;
    }

    return 0;
}
