//solution for https://cses.fi/problemset/task/1649/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

ll a[N];
ll seg[2 * N];

void build(int n) {
    for (int i = 0; i < n; i++) {
        seg[i + n] = a[i];
    }
    for (int i = n - 1; i > 0; i--) {
        seg[i] = min(seg[2 * i], seg[2 * i + 1]);
    }
}

void update(int pos, int val, int n) {
    pos += n;
    seg[pos] = val;
    while (pos > 1) {
        pos /= 2;
        seg[pos] = min(seg[2 * pos], seg[2 * pos + 1]);
    }
}

ll rmq(int l, int r, int n) {
    l += n;
    r += n;
    ll mn = INT_MAX;
    while (l < r) {
        if (r % 2 == 1) {
            mn = min(mn, seg[--r]);
        }
        if (l % 2 == 1) {
            mn = min(mn, seg[l++]);
        }
        l /= 2;
        r /= 2;
    }
    return mn;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(n);
    for (int i = 0; i < q; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        l--, r--;
        if (t == 1) {
            update(l, r + 1, n);
        }
        if (t == 2) {
            cout << rmq(l, r + 1, n) << endl;
        }
    }
    return 0;
}
