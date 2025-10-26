//https://eolymp.com/en/problems/12257
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll INF = 1e18;

int a[N];

pair<ll, int> calc(int d, int n) {
    ll ans = -INF;
    int j;
    for (int i = 0; i < n; i++) {
        ll cur = a[i] - (ll)i * d;
        if (cur > ans) {
            ans = cur;
            j = i;
        } else if (cur == ans) {
            j = i;
        }
    }
    return {ans, j};
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int mx = 0; ll s = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            mx = max(mx, a[i]);
            s += a[i];
        }
        int l = -1e9, r = 1e9, spl = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            auto [_, j] = calc(mid, n);
            if ((ll)n * (n - 1) / 2 - (ll)n * j < 0) {
                l = mid + 1;
            } else {
                r = mid - 1;
                spl = mid;

            }
        }
        ll ans = (ll)n * mx - s;
        for (int i = spl - 3; i <= spl + 3; i++) {
            auto [x, _] = calc(i, n);
            ans = min(ans, (ll)n * x + (ll)n * (n - 1) / 2 * i - s);
        }
        cout << ans << endl;
    }

  return 0;
}
