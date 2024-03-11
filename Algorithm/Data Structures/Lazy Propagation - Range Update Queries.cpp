//solution for https://cses.fi/problemset/task/1651/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

ll a[N];
ll segtree[4 * N];
ll lazy[4 * N];

void updateRange(int pos, int l, int r, int lq, int rq, ll add) {
    if (lazy[pos] != 0) {
        segtree[pos] += (r - l + 1) * lazy[pos];
        if (l != r) {
            lazy[pos * 2 + 1] += lazy[pos];
            lazy[pos * 2 + 2] += lazy[pos];
        }
        lazy[pos] = 0;
    }
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[pos] += (r - l + 1) * add;
        if (l != r) {
            lazy[pos * 2 + 1] += add;
            lazy[pos * 2 + 2] += add;
        }
        return;
    }
    int mid = (l + r) / 2;
    updateRange(pos * 2 + 1, l, mid, lq, rq, add);
    updateRange(pos * 2 + 2, mid + 1, r, lq, rq, add);
    segtree[pos] = segtree[pos * 2 + 1] + segtree[pos * 2 + 2];
}

ll getSum(int l, int r, int lq, int rq, int pos) {
    if (lazy[pos] != 0) {
        segtree[pos] += (r - l + 1) * lazy[pos];
        if (l != r) {
            lazy[pos * 2 + 1] += lazy[pos];
            lazy[pos * 2 + 2] += lazy[pos];
        }
        lazy[pos] = 0;
    }
    if (l > rq || lq > r) {
        return 0;
    }
    if (l >= lq && r <= rq) {
        return segtree[pos];
    }
    int mid = (l + r) / 2;
    return getSum(l, mid, lq, rq, 2 * pos + 1) +
           getSum(mid + 1, r, lq, rq, 2 * pos + 2);
}

void build(int l, int r, int pos) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[pos] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, pos * 2 + 1);
    build(mid + 1, r, pos * 2 + 2);
    segtree[pos] = segtree[pos * 2 + 1] + segtree[pos * 2 + 2];
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            ll u;
            cin >> u;
            updateRange(0, 0, n - 1, l, r, u);
        }
        else{
            int pos;
            cin >> pos;
            pos--;
            cout << getSum(0, n - 1, pos, pos, 0) << endl;
        }
    }
    return 0;
}
