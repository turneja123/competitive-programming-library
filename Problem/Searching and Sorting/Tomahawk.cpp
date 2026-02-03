//https://evaluator.hsin.hr/events/coci26_4/tasks/HONI252645tomahawk/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll INF = 1e18;

vector<pair<char, int>> a;

ll calc(int j, int n, int f) {
    ll ans = 0;
    for (auto [c, x] : a) {
        if (c == 'D') {
            ans += (f ? x : max(0, x - (n - 1)));
        } else if (c == 'L') {
            ans += max(0, x - j);
        } else {
            ans += max(0, x - (n - 1 - j));
        }
    }
    return ans;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;

    for (int i = 0; i < q; i++) {
        char c; int x;
        cin >> c >> x;
        a.push_back({c, x});
    }
    ll mx = max(calc(0, n, 1), calc(n - 1, n, 1));

    ll l = 0, r = n - 1;
    while (r - l >= 3) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;

        ll f1 = -calc(m1, n, 0);
        ll f2 = -calc(m2, n, 0);

        if (f1 < f2) {
            l = m1 + 1;
        } else {
            r = m2 - 1;
        }
    }
    ll mn = INF;
    for (; l <= r; l++) {
        mn = min(mn, calc(l, n, 0));
    }
    cout << mx - mn;
    return 0;
}
