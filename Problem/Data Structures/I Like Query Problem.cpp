//https://atcoder.jp/contests/abc256/tasks/abc256_h
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

struct Node {
    long long sum;
    int mx;
    int mxc;
    Node() {}
    Node(int x) : sum(x), mx(x), mxc(1) {}
};

int a[N];
Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.sum = left.sum + right.sum;
    if (left.mx == right.mx) {
        node.mx = left.mx;
        node.mxc = left.mxc + right.mxc;
    } else if (left.mx > right.mx) {
        node.mx = left.mx;
        node.mxc = left.mxc;
    } else {
        node.mx = right.mx;
        node.mxc = right.mxc;
    }

    return node;
}

void apply_set(int node, int l, int r, int val) {
    segtree[node].sum = (long long)val * (r - l + 1);
    segtree[node].mx = val;
    segtree[node].mxc = r - l + 1;
    return;
}

void compose(int node, int l, int r) {
    if (l == r || segtree[node].mxc < r - l + 1) {
        return;
    }
    int mid = (l + r) / 2;
    apply_set(2 * node + 1, l, mid, segtree[node].mx);
    apply_set(2 * node + 2, mid + 1, r, segtree[node].mx);
    return;
}

long long query_sum(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq) {
        return 0;
    }
    if (lq <= l && rq >= r) {
        return segtree[node].sum;
    }
    compose(node, l, r);
    int mid = (l + r) / 2;
    return query_sum(l, mid, lq, rq, 2 * node + 1) + query_sum(mid + 1, r, lq, rq, 2 * node + 2);
}

void update_set(int l, int r, int lq, int rq, int val, int node) {
    if (r < lq || l > rq) {
        return;
    }
    if (l >= lq && r <= rq) {
        apply_set(node, l, r, val);
        return;
    }
    int mid = (l + r) / 2;
    compose(node, l, r);
    update_set(l, mid, lq, rq, val, 2 * node + 1);
    update_set(mid + 1, r, lq, rq, val, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

void update_div(int l, int r, int lq, int rq, int val, int node) {
    if (r < lq || l > rq) {
        return;
    }
    if (l >= lq && r <= rq && segtree[node].mxc == r - l + 1) {
        apply_set(node, l, r, segtree[node].mx / val);
        return;
    }
    int mid = (l + r) / 2;
    compose(node, l, r);
    update_div(l, mid, lq, rq, val, 2 * node + 1);
    update_div(mid + 1, r, lq, rq, val, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(a[l]);
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
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
        if (t == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            l--, r--;
            update_div(0, n - 1, l, r, x, 0);
        } else if (t == 2) {
            int l, r, x;
            cin >> l >> r >> x;
            l--, r--;
            update_set(0, n - 1, l, r, x, 0);

        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            cout << query_sum(0, n - 1, l, r, 0) << endl;
        }
    }

    return 0;
}
