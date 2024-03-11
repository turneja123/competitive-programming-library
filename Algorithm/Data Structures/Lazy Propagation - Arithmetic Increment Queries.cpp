//solution for https://cses.fi/problemset/task/1736/
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
ll lazy_a[4 * N];

void compose(int parent, int child, int d) {
    lazy_a[child] += lazy_a[parent];
    if (child % 2) {
        lazy[child] += lazy[parent];
    } else {
        lazy[child] += lazy[parent] + lazy_a[parent] * d;
    }
}

void apply(int node, int l, int r) {
    segtree[node] += (r - l + 1) * (2 * lazy[node] + (r - l) * lazy_a[node]) / 2;
    if (l != r) {
        compose(node, 2 * node + 1, (l + r) / 2 - l + 1);
        compose(node, 2 * node + 2, (l + r) / 2 - l + 1);
    }
    lazy[node] = 0;
    lazy_a[node] = 0;
}

void a_incUpdate(int node, int l, int r, int lq, int rq) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        lazy[node] += l - lq + 1;
        lazy_a[node]++;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    a_incUpdate(node * 2 + 1, l, mid, lq, rq);
    a_incUpdate(node * 2 + 2, mid + 1, r, lq, rq);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = segtree[node * 2 + 1] + segtree[node * 2 + 2];
}

ll getSum(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return 0;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node];
    }

    int mid = (l + r) / 2;
    return getSum(l, mid, lq, rq, 2 * node + 1) +
           getSum(mid + 1, r, lq, rq, 2 * node + 2);
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = segtree[node * 2 + 1] + segtree[node * 2 + 2];
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
        int t, l, r;
        cin >> t >> l >> r;
        l--, r--;
        if (t == 1) {
            a_incUpdate(0, 0, n - 1, l, r);
        } else {
            cout << getSum(0, n - 1, l, r, 0) << endl;
        }
    }
    return 0;
}
