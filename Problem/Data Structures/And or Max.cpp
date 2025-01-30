//https://csacademy.com/contest/archive/task/and-or-max/statement/
#pragma GCC optimize("Ofast,fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 20;

struct Node {
    int mx;
    vector<int> bits;
    Node() {
        bits.resize(K, 0);
    }
    Node(int x) : mx(x) {
        bits.resize(K, 0);
        for (int i = 0; i < K; i++) {
            int c = x & (1 << i);
            if (c) {
                bits[i] = 1;
            }
        }
    }
};

int a[N];
Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.mx = max(left.mx, right.mx);
    for (int i = 0; i < K; i++) {
        node.bits[i] = left.bits[i] + right.bits[i];
    }
    return node;
}

void apply_max(int node, int l, int r, int k) {
    int c = segtree[node].mx & (1 << k);
    if (!c) {
        segtree[node].mx ^= (1 << k);
    }
    segtree[node].bits[k] = r - l + 1;
    return;
}

void apply_min(int node, int l, int r, int k) {
    int c = segtree[node].mx & (1 << k);
    if (c) {
        segtree[node].mx ^= (1 << k);
    }
    segtree[node].bits[k] = 0;
    return;
}

void compose(int node, int l, int r, int k) {
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    if (segtree[node].bits[k] == r - l + 1) {
        apply_max(2 * node + 1, l, mid, k);
        apply_max(2 * node + 2, mid + 1, r, k);
    } else if (segtree[node].bits[k] == 0) {
        apply_min(2 * node + 1, l, mid, k);
        apply_min(2 * node + 2, mid + 1, r, k);
    }
    return;
}

int query_max(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq) {
        return 0;
    }
    if (lq <= l && rq >= r) {
        return segtree[node].mx;
    }
    for (int i = 0; i < K; i++) {
        compose(node, l, r, i);
    }
    int mid = (l + r) / 2;
    return max(query_max(l, mid, lq, rq, 2 * node + 1), query_max(mid + 1, r, lq, rq, 2 * node + 2));
}

void update_min(int l, int r, int lq, int rq, int x, int node) {
    if (r < lq || l > rq || x == 0) {
        return;
    }
    for (int i = x; i > 0;) {
        int c = i & (-i);
        int k = __builtin_ctz(c);
        if (l >= lq && r <= rq && segtree[node].bits[k] == r - l + 1) {
            apply_min(node, l, r, k);
            x ^= c;
        } else if (segtree[node].bits[k] == 0) {
            x ^= c;
        }
        i -= c;
    }
    if (x == 0) {
        return;
    }
    int mid = (l + r) / 2;
    for (int i = 0; i < K; i++) {
        compose(node, l, r, i);
    }
    update_min(l, mid, lq, rq, x, 2 * node + 1);
    update_min(mid + 1, r, lq, rq, x, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

void update_max(int l, int r, int lq, int rq, int x, int node) {
    if (r < lq || l > rq || x == 0) {
        return;
    }
    for (int i = x; i > 0;) {
        int c = i & (-i);
        int k = __builtin_ctz(c);
        if (l >= lq && r <= rq && segtree[node].bits[k] == 0) {
            apply_max(node, l, r, k);
            x ^= c;
        } else if (segtree[node].bits[k] == r - l + 1) {
            x ^= c;
        }
        i -= c;
    }
    if (x == 0) {
        return;
    }
    int mid = (l + r) / 2;
    for (int i = 0; i < K; i++) {
        compose(node, l, r, i);
    }
    update_max(l, mid, lq, rq, x, 2 * node + 1);
    update_max(mid + 1, r, lq, rq, x, 2 * node + 2);
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
            x ^= (1 << 20) - 1;
            update_min(0, n - 1, l, r, x, 0);
        } else if (t == 2) {
            int l, r, x;
            cin >> l >> r >> x;
            l--, r--;
            update_max(0, n - 1, l, r, x, 0);

        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            cout << query_max(0, n - 1, l, r, 0) << endl;
        }
    }

    return 0;
}
