//https://atcoder.jp/contests/abc342/tasks/abc342_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

tuple<int, int, int> queries[N];

int a[N];
multiset<int> segtree[4 * N];

void setUpdate(int node, int l, int r, int lq, int rq, int val, int f) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        if (f) {
            segtree[node].insert(val);
        } else {
            segtree[node].erase(segtree[node].find(val));
        }
        return;
    }
    int mid = (l + r) / 2;
    setUpdate(node * 2 + 1, l, mid, lq, rq, val, f);
    setUpdate(node * 2 + 2, mid + 1, r, lq, rq, val, f);
}

int getMax(int l, int r, int ind, int node) {
    int mid = (l + r) / 2;
    int mx = 0;
    if (segtree[node].size()) {
        mx = max(mx, *segtree[node].rbegin());
    }
    if (l == r) {
        return mx;
    }
    if (ind <= mid) {
        return max(mx, getMax(l, mid, ind, 2 * node + 1));
    }
    return max(mx, getMax(mid + 1, r, ind, 2 * node + 2));
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node].insert(a[l]);
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
}

int main() {
    IOS;
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(0, n - 1, 0);
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            l--, r--;
            queries[i] = make_tuple(l, r, x);
            setUpdate(0, 0, n - 1, l, r, x, 1);
        } else if (t == 2) {
            int j;
            cin >> j;
            j--;
            auto [l, r, x] = queries[j];
            setUpdate(0, 0, n - 1, l, r, x, 0);
        } else {
            int j;
            cin >> j;
            j--;
            cout << getMax(0, n - 1, j, 0) << endl;
        }
    }
    return 0;
}

