//https://cses.fi/problemset/task/1735
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

struct Node {
    bool setValid;
    long long setVal;
    long long sum;
    long long lazy;
    Node() {
        setValid = 0, setVal = 0, lazy = 0;
    }
    Node(long long x) : setValid(0), setVal(0), sum(x), lazy(0) {}
};

int a[N];
Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.sum = left.sum + right.sum;
    return node;
}

void compose(int parent, int child) {
    if (segtree[parent].setValid) {
        segtree[child].setValid = 1;
        segtree[child].setVal = segtree[parent].setVal;
        segtree[child].lazy = segtree[parent].lazy;
    } else {
        segtree[child].lazy += segtree[parent].lazy;
    }
}

void apply(int node, int l, int r) {
    if (segtree[node].setValid) {
        segtree[node].sum = segtree[node].setVal * (r - l + 1);
    }
    segtree[node].sum += segtree[node].lazy * (r - l + 1);
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    segtree[node].setValid = false;
    segtree[node].lazy = 0;
}

void incUpdate(int node, int l, int r, int lq, int rq, ll add) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].lazy += add;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq, add);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

void setUpdate(int node, int l, int r, int lq, int rq, ll val) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].setValid = true;
        segtree[node].setVal = val;
        segtree[node].lazy = 0;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    setUpdate(node * 2 + 1, l, mid, lq, rq, val);
    setUpdate(node * 2 + 2, mid + 1, r, lq, rq, val);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

long long getSum(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return 0;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node].sum;
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
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
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
        if (t == 1 || t == 2) {
            int l, r, u;
            cin >> l >> r >> u;
            l--, r--;
            if (t == 1) {
                incUpdate(0, 0, n - 1, l, r, u);
            } else {
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
    return 0;
}
