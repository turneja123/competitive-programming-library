//https://atcoder.jp/contests/arc123/tasks/arc123_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

__int128 calc(vector<int> &a, ll add) {
    int n = a.size();
    __int128 l, r;
    if (a[0] >= 0) {
        l = -add;
        r = a[0] + add;
    } else {
        l = a[0] - add;
        r = add;
    }
    __int128 ans = abs(l) + abs(r);
    for (int i = 1; i < n; i++) {
        if (l + r > a[i]) {
            r -= (l + r) - a[i];
        } else if (l + r < a[i]) {
            l += a[i] - (l + r);
        }
        ans += abs(l) + abs(r);
    }
    return ans;
}

int main() {
    IOS;
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll l = 0, r = 1e18;
    while (r - l >= 3) {
        ll m1 = l + (r - l) / 3;
        ll m2 = r - (r - l) / 3;

        __int128 f1 = -calc(a, m1);
        __int128 f2 = -calc(a, m2);

        if (f1 < f2) {
            l = m1 + 1;
        } else {
            r = m2 - 1;
        }
    }
    __int128 ans = 8e18;
    for (; l <= r; l++) {
        ans = min(ans, calc(a, l));
    }
    cout << (ll)ans;

    return 0;
}
