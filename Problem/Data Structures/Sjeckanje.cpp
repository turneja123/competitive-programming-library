//https://dmoj.ca/problem/coci20c5p5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long INF = 4e18;

struct Node {
    long long val[3][3];
    long long lazy;
    Node() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                val[i][j] = 0;
            }
        }
        lazy = 0;
    }
    Node(long long x) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                val[i][j] = -INF;
            }
        }
        val[0][0] = 0;
        val[0][1] = -x;
        val[1][0] = -x;
        val[0][2] = x;
        val[2][0] = x;
        lazy = 0;
    }
};

Node segtree[4 * N];
long long a[N];

Node combine(Node left, Node right) {
    Node node = Node();

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            node.val[i][j] = max({left.val[i][0] + right.val[0][j], left.val[i][1] + right.val[2][j], left.val[i][2] + right.val[1][j], left.val[i][j], right.val[i][j]});
        }
    }
    return node;
}

void compose(int parent, int child) {
    segtree[child].lazy += segtree[parent].lazy;
}

void apply(int node, int l, int r) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (segtree[node].val[i][j] == -INF) {
                continue;
            }
            long long add = 0;
            if (i == 1) {
                add -= segtree[node].lazy;
            } else if (i == 2) {
                add += segtree[node].lazy;
            }
            if (j == 1) {
                add -= segtree[node].lazy;
            } else if (j == 2) {
                add += segtree[node].lazy;
            }
            segtree[node].val[i][j] += add;
        }
    }
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
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
        int l, r, x;
        cin >> l >> r >> x;
        l--, r--;
        incUpdate(0, 0, n - 1, l, r, x);
        apply(0, 0, n - 1);
        cout << segtree[0].val[0][0] << endl;
    }

    return 0;
}
