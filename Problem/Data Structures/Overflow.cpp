//https://dmoj.ca/problem/olep1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long INF = 1e14;

struct Node {
    long long sum_cap;
    long long sum_free;
    long long mn;
    long long mx;
    bool lazy;
    long long lazy_inc;
    Node() {
        lazy = false;
        lazy_inc = 0;
    }
    Node(long long x) : sum_cap(x), sum_free(x), mn(x), mx(x), lazy(false), lazy_inc(0) {}
};

Node segtree[4 * N];
long long a[N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.sum_cap = left.sum_cap + right.sum_cap;
    node.sum_free = left.sum_free + right.sum_free;
    node.mx = max(left.mx, right.mx);
    node.mn = min(left.mn, right.mn);
    return node;
}

void compose(int parent, int child) {
    segtree[child].lazy |= segtree[parent].lazy;
    segtree[child].lazy_inc += segtree[parent].lazy_inc;
}

void apply(int node, int l, int r) {
    if (segtree[node].lazy) {
        segtree[node].sum_free = 0;
        segtree[node].lazy_inc = 0;
        segtree[node].mx = 0;
        segtree[node].mn = 0;
    } else {
        segtree[node].sum_free -= segtree[node].lazy_inc * (r - l + 1);
        segtree[node].mx -= segtree[node].lazy_inc;
        segtree[node].mn -= segtree[node].lazy_inc;
    }
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    segtree[node].lazy = false;
    segtree[node].lazy_inc = 0;
}

long long query(int l, int r, int ind, int node) {
    apply(node, l, r);
    if (l == r) {
        return segtree[node].sum_cap - segtree[node].sum_free;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        return query(l, mid, ind, 2 * node + 1);
    } else {
        return query(mid + 1, r, ind, 2 * node + 2);
    }
}

long long o_val;

void traverse(int l, int r, int node) {
    apply(node, l, r);
    if (l == r) {
        segtree[node].sum_free -= o_val;
        segtree[node].mx = segtree[node].sum_free;
        segtree[node].mn = segtree[node].sum_free;
        o_val = 0;
        return;
    }
    int mid = (l + r) / 2;
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    if (segtree[2 * node + 1].sum_free <= o_val) {
        o_val -= segtree[2 * node + 1].sum_free;
        segtree[2 * node + 1].lazy = true;
        traverse(mid + 1, r, 2 * node + 2);
    } else {
        traverse(l, mid, 2 * node + 1);
    }
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

void overflow(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq || o_val == 0) {
        return;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        if (segtree[node].sum_free <= o_val) {
            o_val -= segtree[node].sum_free;
            segtree[node].lazy = true;
            return;
        }
        traverse(l, r, node);
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    overflow(l, mid, lq, rq, 2 * node + 1);
    overflow(mid + 1, r, lq, rq, 2 * node + 2);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

void update(int l, int r, int lq, int rq, long long val, int node, int n) {
    if (l > rq || r < lq) {
        return;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq && segtree[node].mn >= val) {
        segtree[node].lazy_inc += val;
        return;
    }
    if (l >= lq && r <= rq && segtree[node].mx <= val) {
        o_val = val * (r - l + 1) - segtree[node].sum_free;
        segtree[node].lazy = true;
        overflow(0, n - 1, r + 1, n - 1, 0);
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    update(l, mid, lq, rq, val, 2 * node + 1, n);
    update(mid + 1, r, lq, rq, val, 2 * node + 2, n);

    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);

    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

void update_cap(int l, int r, int ind, long long val, int node, int n) {
    apply(node, l, r);
    if (l == r) {
        long long has = segtree[node].sum_cap - segtree[node].sum_free;
        segtree[node].sum_cap = val;
        if (segtree[node].sum_cap < has) {
            o_val = has - segtree[node].sum_cap;
            segtree[node].sum_free = 0;
            overflow(0, n - 1, l + 1, n - 1, 0);
        } else {
            segtree[node].sum_free = segtree[node].sum_cap - has;
        }
        segtree[node].mn = segtree[node].sum_free;
        segtree[node].mx = segtree[node].sum_free;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update_cap(l, mid, ind, val, 2 * node + 1, n);
    } else {
        update_cap(mid + 1, r, ind, val, 2 * node + 2, n);
    }
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
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
            int l, r; long long x;
            cin >> l >> r >> x;
            l--, r--;
            update(0, n - 1, l, r, x, 0, n);
        } else if (t == 2) {
            int j; long long x;
            cin >> j >> x;
            j--;
            update_cap(0, n - 1, j, x, 0, n);
        } else {
            int j;
            cin >> j;
            j--;
            cout << query(0, n - 1, j, 0) << endl;
        }
    }

    return 0;
}
