//solution for https://dmoj.ca/problem/wac6p3
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

ll a[N];
ll srch[N];
ll diff[N];

ll seg[2 * N];

map <ll, int> ct;
map <ll, vector<ll>> mp;

void build(int n) {
    for (int i = 0; i < n; i++) {
        seg[i + n] = diff[i];
    }
    for (int i = n - 1; i > 0; i--) {
        seg[i] = max(seg[2 * i], seg[2 * i + 1]);
    }
}

ll rmq(int l, int r, int n) {
    l += n;
    r += n;
    ll mx = 0;
    while (l < r) {
        if (r % 2 == 1) {
            mx = max(mx, seg[--r]);
        }
        if (l % 2 == 1) {
            mx = max(mx, seg[l++]);
        }
        l /= 2;
        r /= 2;
    }
    return mx;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        diff[i] = a[i];
        auto it = mp.find(a[i]);
        if (it == mp.end()) {
            vector<ll> v;
            v.push_back(i);
            mp.insert({a[i], v});
        } else {
            it->second.push_back(i);
        }

        auto j = ct.find(a[i]);
        if (j == ct.end()) {
            ct.insert({a[i], 1});
        } else {
            j->second++;
        }
    }
    sort(diff, diff + n);
    for (int i = 0; i < n - 1; i++) {
        srch[i] = diff[i];
        diff[i] = diff[i + 1] - diff[i];
    }
    build(n - 1);
    ll ans = 0;
    for (int i = 0; i < n - 1; i++) {
        int pos = lower_bound(srch, srch + n - 1, a[i]) - srch;
        ans = max(ans, rmq(i, pos, n - 1));
        int swp = mp[srch[i]][ct[srch[i]] - 1];
        if (a[i] > a[swp]) {
            swap(a[i], a[swp]);
            ct[srch[i]]--;
        }
    }
    cout << ans << endl;
    return 0;
}
