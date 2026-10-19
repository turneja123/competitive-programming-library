//bbc18q
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll INF = 1e18;

int main() {
    IOS;
    int n;
    cin >> n;
    vector<pair<int, int>> v;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        v.push_back({x, y});
    }

    ll ans = INF;
    for (int j = 0; j < 2; j++) {
        ll mx = 0; int ok = 1;
        for (int i = 0; i < n; i++) {
            auto [x, y] = v[i];
            ll mn = INF;
            if (x % 2 == j) {
                mn = min(mn, (ll)x);
            }
            if (y % 2 == j) {
                mn = min(mn, (ll)y);
            }
            if (mn == INF) {
                ok = 0;
                break;
            }
            mx = max(mx, mn);
        }
        if (ok == 1) {
            ans = min(ans, mx);
        }
    }
    if (ans == INF) {
        ans = -1;
    }
    cout << ans;


    return 0;
}
