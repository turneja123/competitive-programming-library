//https://www.spoj.com/problems/SEGSQRSS/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

long long a[N];
long long segtree[4 * N];
long long segtree_sq[4 * N];

long long lazy[4 * N];
long long setVal[4 * N];
bool setValid[4 * N];

void compose(int parent, int child) {
    if (setValid[parent]) {
        setValid[child] = 1;
        setVal[child] = setVal[parent];
        lazy[child] = lazy[parent];
    } else {
        lazy[child] += lazy[parent];
    }
}

void apply(int node, int l, int r) {
    if (setValid[node]) {
        segtree[node] = (r - l + 1) * setVal[node];
        segtree_sq[node] = (r - l + 1) * setVal[node] * setVal[node];
    }
    segtree_sq[node] += segtree[node] * lazy[node] * 2  + (r - l + 1) * lazy[node] * lazy[node];
    segtree[node] += (r - l + 1) * lazy[node];
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    setValid[node] = false;
    lazy[node] = 0;
}

void incUpdate(int node, int l, int r, int lq, int rq, ll add) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        lazy[node] += add;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq, add);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = segtree[node * 2 + 1] + segtree[node * 2 + 2];
    segtree_sq[node] = segtree_sq[node * 2 + 1] + segtree_sq[node * 2 + 2];
}

void setUpdate(int node, int l, int r, int lq, int rq, ll val) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        setValid[node] = true;
        setVal[node] = val;
        lazy[node] = 0;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    setUpdate(node * 2 + 1, l, mid, lq, rq, val);
    setUpdate(node * 2 + 2, mid + 1, r, lq, rq, val);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = segtree[node * 2 + 1] + segtree[node * 2 + 2];
    segtree_sq[node] = segtree_sq[node * 2 + 1] + segtree_sq[node * 2 + 2];
}

ll getSum(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return 0;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree_sq[node];
    }
    int mid = (l + r) / 2;
    return getSum(l, mid, lq, rq, 2 * node + 1) +
           getSum(mid + 1, r, lq, rq, 2 * node + 2);
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    lazy[node] = 0;
    setValid[node] = 0;
    setVal[node] = 0;
    if (l == r) {
        segtree[node] = a[l];
        segtree_sq[node] = a[l] * a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = segtree[node * 2 + 1] + segtree[node * 2 + 2];
    segtree_sq[node] = segtree_sq[node * 2 + 1] + segtree_sq[node * 2 + 2];
}

int main() {
    IOS;
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        build(0, n - 1, 0);
        cout << "Case " << tt << ": " << endl;
        for (int i = 0; i < q; i++) {
            int t;
            cin >> t;
            if (t == 1 || t == 0) {
                int l, r;
                cin >> l >> r;
                l--, r--;
                ll u;
                cin >> u;
                if (t == 1) {
                    incUpdate(0, 0, n - 1, l, r, u);
                }
                else {
                    setUpdate(0, 0, n - 1, l, r, u);
                }
            }
            else{
                int l, r;
                cin >> l >> r;
                l--, r--;
                cout << getSum(0, n - 1, l, r, 0) << endl;
            }
        }
    }
    return 0;
}
