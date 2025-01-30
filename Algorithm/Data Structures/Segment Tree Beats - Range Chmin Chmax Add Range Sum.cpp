//https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long INF = 1e18;

struct Node {
    long long sum;
    long long lazy;
    long long mx1;
    long long mx2;
    long long mxc;
    long long mn1;
    long long mn2;
    long long mnc;
    Node() : sum(0), lazy(0), mx1(0), mx2(0), mxc(0), mn1(0), mn2(0), mnc(0) {}
    Node(long long x) : sum(x), lazy(0), mx1(x), mx2(-INF), mxc(1), mn1(x), mn2(INF), mnc(1) {}
};

long long a[N];
Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.sum = left.sum + right.sum;
    if (left.mx1 == right.mx1) {
        node.mx1 = left.mx1;
        node.mx2 = max(left.mx2, right.mx2);
        node.mxc = left.mxc + right.mxc;
    } else if (left.mx1 > right.mx1) {
        node.mx1 = left.mx1;
        node.mx2 = max(left.mx2, right.mx1);
        node.mxc = left.mxc;
    } else {
        node.mx1 = right.mx1;
        node.mx2 = max(left.mx1, right.mx2);
        node.mxc = right.mxc;
    }
    if (left.mn1 == right.mn1) {
        node.mn1 = left.mn1;
        node.mn2 = min(left.mn2, right.mn2);
        node.mnc = left.mnc + right.mnc;
    } else if (left.mn1 < right.mn1) {
        node.mn1 = left.mn1;
        node.mn2 = min(left.mn2, right.mn1);
        node.mnc = left.mnc;
    } else {
        node.mn1 = right.mn1;
        node.mn2 = min(left.mn1, right.mn2);
        node.mnc = right.mnc;
    }
    return node;
}

void apply_max(int node, int l, int r, long long val) {
    if (segtree[node].mx1 <= val) {
        return;
    }
    segtree[node].sum -= (long long)(segtree[node].mx1 - val) * segtree[node].mxc;
    segtree[node].mx1 = val;
    if (l == r) {
        segtree[node].mn1 = segtree[node].mx1;
    } else {
        if (val <= segtree[node].mn1) {
            segtree[node].mn1 = val;
        } else if (val < segtree[node].mn2) {
            segtree[node].mn2 = val;
        }
    }
    return;
}

void apply_min(int node, int l, int r, long long val) {
    if (segtree[node].mn1 >= val) {
        return;
    }
    segtree[node].sum -= (long long)(segtree[node].mn1 - val) * segtree[node].mnc;
    segtree[node].mn1 = val;
    if (l == r) {
        segtree[node].mx1 = segtree[node].mn1;
    } else {
        if (val >= segtree[node].mx1) {
            segtree[node].mx1 = val;
        } else if (val > segtree[node].mx2) {
            segtree[node].mx2 = val;
        }
    }
    return;
}

void apply_add(int node, int l, int r, long long val) {
    if (val == 0) {
        return;
    }
    segtree[node].sum += val * (r - l + 1);
    segtree[node].mx1 += val;
    if (segtree[node].mx2 != -INF) {
        segtree[node].mx2 += val;
    }
    segtree[node].mn1 += val;
    if (segtree[node].mn2 != INF) {
        segtree[node].mn2 += val;
    }
    segtree[node].lazy += val;
    return;
}

void compose(int node, int l, int r) {
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    apply_add(2 * node + 1, l, mid, segtree[node].lazy);
    apply_add(2 * node + 2, mid + 1, r, segtree[node].lazy);
    segtree[node].lazy = 0;
    apply_max(2 * node + 1, l, mid, segtree[node].mx1);
    apply_max(2 * node + 2, mid + 1, r, segtree[node].mx1);
    apply_min(2 * node + 1, l, mid, segtree[node].mn1);
    apply_min(2 * node + 2, mid + 1, r, segtree[node].mn1);
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

void update_min(int l, int r, int lq, int rq, long long val, int node) {
    if (r < lq || l > rq || segtree[node].mx1 <= val) {
        return;
    }
    if (l >= lq && r <= rq && segtree[node].mx2 < val) {
        apply_max(node, l, r, val);
        return;
    }
    int mid = (l + r) / 2;
    compose(node, l, r);
    update_min(l, mid, lq, rq, val, 2 * node + 1);
    update_min(mid + 1, r, lq, rq, val, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

void update_max(int l, int r, int lq, int rq, long long val, int node) {
    if (r < lq || l > rq || segtree[node].mn1 >= val) {
        return;
    }
    if (l >= lq && r <= rq && segtree[node].mn2 > val) {
        apply_min(node, l, r, val);
        return;
    }
    int mid = (l + r) / 2;
    compose(node, l, r);
    update_max(l, mid, lq, rq, val, 2 * node + 1);
    update_max(mid + 1, r, lq, rq, val, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

void update_add(int l, int r, int lq, int rq, long long val, int node) {
    if (r < lq || l > rq) {
        return;
    }
    if (l >= lq && r <= rq) {
        apply_add(node, l, r, val);
        return;
    }
    int mid = (l + r) / 2;
    compose(node, l, r);
    update_add(l, mid, lq, rq, val, 2 * node + 1);
    update_add(mid + 1, r, lq, rq, val, 2 * node + 2);
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
        if (t == 0) {
            int l, r; long long x;
            cin >> l >> r >> x;
            r--;
            update_min(0, n - 1, l, r, x, 0);
        } else if (t == 1) {
            int l, r; long long x;
            cin >> l >> r >> x;
            r--;
            update_max(0, n - 1, l, r, x, 0);
        } else if (t == 2) {
            int l, r; long long x;
            cin >> l >> r >> x;
            r--;
            update_add(0, n - 1, l, r, x, 0);
        } else {
            int l, r;
            cin >> l >> r;
            r--;
            cout << query_sum(0, n - 1, l, r, 0) << endl;
        }
    }

    return 0;
}
