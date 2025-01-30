//https://codeforces.com/contest/1093/problem/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 16;

int k;

struct Node {
    vector<int> data;
    vector<int> mask_mx;
    vector<int> mask_mn;
    int best;
    Node() {
        mask_mx.resize(K);
        mask_mn.resize(K);
        best = -1;
    }
    Node(vector<int> x) {
        data = x;
        mask_mx.resize(K);
        mask_mn.resize(K);
        for (int mask = 1 << (k - 1); mask < (1 << k); mask++) {
            int cur = 0;
            for (int j = 0; j < k; j++) {
                int c = mask & (1 << j);
                if (c != 0) {
                    cur += data[j];
                } else {
                    cur -= data[j];
                }
            }
            mask_mx[mask - (1 << (k - 1))] = cur;
            mask_mn[mask - (1 << (k - 1))] = cur;
        }
        best = 0;
    }
};

Node segtree[4 * N];
vector<int> a[N];

Node combine(Node left, Node right) {
    Node node = Node();
    if (left.best == -1) {
        return right;
    }
    if (right.best == -1) {
        return left;
    }
    node.best = max(left.best, right.best);
    for (int mask = 1 << (k - 1); mask < (1 << k); mask++) {
        node.mask_mx[mask - (1 << (k - 1))] = max(left.mask_mx[mask - (1 << (k - 1))], right.mask_mx[mask - (1 << (k - 1))]);
        node.mask_mn[mask - (1 << (k - 1))] = min(left.mask_mn[mask - (1 << (k - 1))], right.mask_mn[mask - (1 << (k - 1))]);
        node.best = max(node.best, node.mask_mx[mask - (1 << (k - 1))] - node.mask_mn[mask - (1 << (k - 1))]);
    }
    return node;
}

Node query(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq) {
        Node sentinel;
        return sentinel;
    }

    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    int mid = (l + r) / 2;
    return combine(query(l, mid, lq, rq, 2 * node + 1), query(mid + 1, r, lq, rq, 2 * node + 2));
}

void update(int l, int r, int ind, vector<int> val, int node) {
    if (l == r) {
        segtree[node] = Node(val);
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2);
    }
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
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        a[i].resize(k);
        for (int j = 0; j < k; j++) {
            cin >> a[i][j];
        }
    }
    build(0, n - 1, 0);
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int ind;
            cin >> ind;
            ind--;
            vector<int> v(k);
            for (int j = 0; j < k; j++) {
                cin >> v[j];
            }
            update(0, n - 1, ind, v, 0);
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            cout << query(0, n - 1, l, r, 0).best << endl;
        }
    }
    return 0;
}
