#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

pair<ll, ll> a[N];

int main() {
    IOS;
    int n; ll x;
    cin >> n >> x;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    pair<ll, ll> s = {x, -1};
    int pos = lower_bound(a, a + n, s) - a;
    int r = pos, l = pos - 1;
    ll cur = x;
    ll sol = 0;
    ll tot = a[r].first - x;
    while (r < n) {

        if (l == -1) {
            sol++;
            break;
        }
        if (a[r].second > a[l].second) {
            sol += 2 * (a[l].second);
            tot += 2 * (a[l].second) * (a[r].first - a[l].first);
            a[r].second -= a[l].second;
            l--;
        } else {
            sol += 2 * (a[r].second);
            tot += 2 * (a[r].second) * (a[r].first - a[l].first) - (a[r].first - a[l].first);
            a[l].second -= a[r].second;
            r++;
            if (r != n) {
                tot += a[r].first - a[l].first;
            }
            if (a[l].second == 0) {
                l--;
            }
        }
    }
    cout << sol << endl << tot;
    return 0;
}
