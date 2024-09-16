//https://dmoj.ca/problem/dqu
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int segtree[4 * N];
int lazy[4 * N];
int setVal[4 * N];
bool setValid[4 * N];
int sum[4 * N];

int ind = -1;

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
        segtree[node] = setVal[node];
    }
    segtree[node] += lazy[node];
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    setValid[node] = false;
    lazy[node] = 0;
}

void incUpdate(int node, int l, int r, int lq, int rq, int add) {
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
    segtree[node] = min(segtree[node * 2 + 1], segtree[node * 2 + 2]);
}

void setUpdate(int node, int l, int r, int lq, int rq, int val) {
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
    segtree[node] = min(segtree[node * 2 + 1], segtree[node * 2 + 2]);
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
    segtree[node] = min(segtree[node * 2 + 1], segtree[node * 2 + 2]);
}

void findMin(int l, int r, int node) {
    apply(node, l, r);
    if (l == r) {
        ind = l;
        return;
    }
    int mid = (l + r) / 2;
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    if (segtree[2 * node + 1] <= segtree[2 * node + 2]) {
        findMin(l, mid, 2 * node + 1);
    } else {
        findMin(mid + 1, r, 2 * node + 2);
    }
    return;
}

void update(int l, int r, int node, int ind) {
    if (l == r) {
        sum[node]++;
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        update(l, mid, 2 * node + 1, ind);
    } else {
        update(mid + 1, r, 2 * node + 2, ind);
    }
    sum[node] = sum[2 * node + 1] + sum[2 * node + 2];
    return;
}

int query(int l, int r, int node, int lq, int rq) {
    if (l > rq || r < lq) {
        return 0;
    }
    if (l >= lq && r <= rq) {
        return sum[node];
    }
    int mid = (l + r) / 2;
    return query(l, mid, 2 * node + 1, lq, rq) + query(mid + 1, r, 2 * node + 2, lq, rq);
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    n = min(n, q);
    a[0] = N;
    for (int i = 1; i <= n; i++) {
        a[i] = i;
    }
    build(0, n, 0);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r;
            cin >> l >> r;
            incUpdate(0, 0, n, l, r, -1);
            while (segtree[0] == 0) {
                findMin(0, n, 0);
                setUpdate(0, 0, n, ind, ind, ind);
                update(0, n, 0, ind);
            }
        } else {
            int l, r;
            cin >> l >> r;
            cout << query(0, n, 0, l, r) << endl;
        }
    }


    return 0;
}
