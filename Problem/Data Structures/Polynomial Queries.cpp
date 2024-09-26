//https://cses.fi/problemset/task/1736/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

long long a[N];
long long lazy[4 * N];
long long lazy_a[4 * N];
long long segtree[4 * N];

void apply(int l, int r, int node) {
    segtree[node] = segtree[node] + lazy[node] * (r - l + 1) + lazy_a[node] * (r - l + 1) * (r - l + 2) / 2;
    if (l != r) {
        lazy[2 * node + 1] += lazy[node];
        lazy_a[2 * node + 1] += lazy_a[node];
        lazy[2 * node + 2] += lazy[node] + lazy_a[node] * ((l + r) / 2 - l + 1);
        lazy_a[2 * node + 2] += lazy_a[node];
    }
    lazy[node] = 0;
    lazy_a[node] = 0;
}

void incUpdate(int l, int r, int node, int lq, int rq) {
    if (l > rq || r < lq) {
        return;
    }
    if (l >= lq && r <= rq) {
        lazy[node] += l - lq;
        lazy_a[node]++;
        return;
    }
    apply(l, r, node);
    int mid = (l + r) / 2;
    incUpdate(l, mid, 2 * node + 1, lq, rq);
    incUpdate(mid + 1, r, 2 * node + 2, lq, rq);
    apply(l, mid, 2 * node + 1);
    apply(mid + 1, r, 2 * node + 2);
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
}

long long query(int l, int r, int node, int lq, int rq) {
    if (l > rq || r < lq) {
        return 0;
    }
    apply(l, r, node);
    if (l >= lq && r <= rq) {
        return segtree[node];
    }
    int mid = (l + r) / 2;
    return query(l, mid, 2 * node + 1, lq, rq) + query(mid + 1, r, 2 * node + 2, lq, rq);
}

void build(int l, int r, int node) {
    if (l == r) {
        segtree[node] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
}

int main(){
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        l--, r--;
        if (t == 1) {
            incUpdate(0, n - 1, 0, l, r);
        } else {
            cout << query(0, n - 1, 0, l, r) << endl;
        }
    }
    return 0;
}
