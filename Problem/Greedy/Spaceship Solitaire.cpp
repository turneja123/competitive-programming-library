//https://codeforces.com/contest/1266/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];


int main() {
    IOS;
    int n;
    cin >> n;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        ans += a[i];
    }
    int l = 0, r = 0, q;
    cin >> q;
    map<pair<int, int>, int> mp;
    for (int i = 0; i < q; i++) {
        int u, x, v;
        cin >> u >> x >> v;
        u--, v--;

        auto add = [&](int u, int x, int v) -> void {
            if (a[u] >= x) {
                l++;
            } else {
                r--;
            }
            if (mp.find({v, a[v]}) != mp.end()) {
                l--;
            }
            if (a[v] > 0) {
                ans--;
            }
            a[v]--;
            mp[{u, x}] = v;
        };

        auto rem = [&](int u, int x, int v) -> void {
            if (a[u] >= x) {
                l--;
            } else {
                r++;
            }
            a[v]++;
            if (a[v] > 0) {
                ans++;
            }
            if (mp.find({v, a[v]}) != mp.end()) {
                l++;
            }
            mp.erase({u, x});
        };

        if (mp.find({u, x}) != mp.end()) {
            rem(u, x, mp[{u, x}]);
        }
        if (v != -1) {
            add(u, x, v);
        }
        cout << ans + (l <= r) - mp.empty() << endl;
    }

    return 0;
}
