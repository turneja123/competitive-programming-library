//https://vjudge.net/problem/HDU-5306
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int INF = 2e9;

struct Node {
    long long sum;
    int mx1;
    int mx2;
    int mxc;
    Node() : sum(0), mx1(0), mx2(0), mxc(0) {}
    Node(int x) : sum(x), mx1(x), mx2(-INF), mxc(1) {}
};

int a[N];
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
    return node;
}

void apply(int node, int l, int r, int val) {
    if (segtree[node].mx1 <= val) {
        return;
    }
    segtree[node].sum -= (long long)(segtree[node].mx1 - val) * segtree[node].mxc;
    segtree[node].mx1 = val;
    return;
}


long long query_sum(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq) {
        return 0;
    }

    if (lq <= l && rq >= r) {
        return segtree[node].sum;
    }
    int mid = (l + r) / 2;
    apply(2 * node + 1, l, mid, segtree[node].mx1);
    apply(2 * node + 2, mid + 1, r, segtree[node].mx1);
    return query_sum(l, mid, lq, rq, 2 * node + 1) + query_sum(mid + 1, r, lq, rq, 2 * node + 2);
}

int query_max(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq) {
        return -INF;
    }
    if (lq <= l && rq >= r) {
        return segtree[node].mx1;
    }
    int mid = (l + r) / 2;
    apply(2 * node + 1, l, mid, segtree[node].mx1);
    apply(2 * node + 2, mid + 1, r, segtree[node].mx1);
    return max(query_max(l, mid, lq, rq, 2 * node + 1), query_max(mid + 1, r, lq, rq, 2 * node + 2));
}

void update(int l, int r, int lq, int rq, int val, int node) {
    if (r < lq || l > rq || segtree[node].mx1 <= val) {
        return;
    }
    if (l >= lq && r <= rq && segtree[node].mx2 < val) {
        apply(node, l, r, val);
        return;
    }
    int mid = (l + r) / 2;
    apply(2 * node + 1, l, mid, segtree[node].mx1);
    apply(2 * node + 2, mid + 1, r, segtree[node].mx1);
    update(l, mid, lq, rq, val, 2 * node + 1);
    update(mid + 1, r, lq, rq, val, 2 * node + 2);
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
    int t;
    cin >> t;
    while (t--) {
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
                int l, r, x;
                cin >> l >> r >> x;
                l--, r--;
                update(0, n - 1, l, r, x, 0);
            } else if (t == 1) {
                int l, r;
                cin >> l >> r;
                l--, r--;
                cout << query_max(0, n - 1, l, r, 0) << endl;
            } else {
                int l, r;
                cin >> l >> r;
                l--, r--;
                cout << query_sum(0, n - 1, l, r, 0) << endl;
            }
        }
    }
    return 0;
}
