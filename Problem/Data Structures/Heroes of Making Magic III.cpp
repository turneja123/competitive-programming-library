//https://codeforces.com/contest/717/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll INF = 1e18;

int a[N];

struct Node {
    ll pref_mn[2][2];
    ll sum[2];
    ll lazy;
    int sz;
    int sentinel;

    Node() {
        sentinel = 1;
        lazy = 0;
        sz = 0;
        pref_mn[0][0] = INF, pref_mn[0][1] = INF;
        pref_mn[1][0] = INF, pref_mn[1][1] = INF;
    }

    Node(int x) {
        sz = 1;
        sentinel = 0;
        lazy = 0;
        sum[0] = x;
        sum[1] = -x;
        pref_mn[0][0] = INF, pref_mn[0][1] = INF;
        pref_mn[1][0] = INF, pref_mn[1][1] = INF;
        pref_mn[0][0] = x;
        pref_mn[1][1] = -x;

    }

};

Node combine(Node left, Node right) {
    if (left.sentinel) {
        return right;
    }
    if (right.sentinel) {
        return left;
    }
    Node node;
    node.sentinel = 0;
    node.sz = left.sz + right.sz;
    node.pref_mn[0][0] = left.pref_mn[0][0], node.pref_mn[0][1] = left.pref_mn[0][1];
    node.pref_mn[1][0] = left.pref_mn[1][0], node.pref_mn[1][1] = left.pref_mn[1][1];

    if (left.sz % 2 == 0) {
        node.sum[0] = left.sum[0] + right.sum[0];
        node.sum[1] = left.sum[1] + right.sum[1];
    } else {
        node.sum[0] = left.sum[0] + right.sum[1];
        node.sum[1] = left.sum[1] + right.sum[0];
    }
    for (int l = 0; l < 2; l++) {
        int r_l = l ^ (left.sz & 1);
        for (int r_r = 0; r_r < 2; r_r++) {
            node.pref_mn[l][r_r] = min(node.pref_mn[l][r_r], left.sum[l] + right.pref_mn[r_l][r_r]);
        }
    }

    return node;
}


Node nodes[4 * N];

void apply(int l, int r, int node) {
    if ((r - l + 1) % 2 == 1) {
        nodes[node].sum[0] += nodes[node].lazy;
        nodes[node].sum[1] -= nodes[node].lazy;
    }
    nodes[node].pref_mn[0][0] += nodes[node].lazy;
    nodes[node].pref_mn[1][1] -= nodes[node].lazy;

    if (l != r) {
        nodes[2 * node + 1].lazy += nodes[node].lazy;
        nodes[2 * node + 2].lazy += nodes[node].lazy;
    }
    nodes[node].lazy = 0;
}

void upd(int l, int r, int node, int lq, int rq, int val) {
    if (l > rq || r < lq || l > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        nodes[node].lazy += val;
        return;
    }
    apply(l, r, node);
    int mid = (l + r) / 2;
    upd(l, mid, 2 * node + 1, lq, rq, val);
    upd(mid + 1, r, 2 * node + 2, lq, rq, val);
    apply(l, mid, 2 * node + 1);
    apply(mid + 1, r, 2 * node + 2);
    nodes[node] = combine(nodes[2 * node + 1], nodes[2 * node + 2]);
    return;
}

Node query(int l, int r, int node, int lq, int rq) {
    if (l > rq || r < lq || l > r) {
        Node sentinel;
        return sentinel;
    }
    apply(l, r, node);
    if (l >= lq && r <= rq) {
        return nodes[node];
    }
    int mid = (l + r) / 2;
    return combine(query(l, mid, 2 * node + 1, lq, rq), query(mid + 1, r, 2 * node + 2, lq, rq));
}

void build(int l, int r, int node) {
    if (l == r) {
        nodes[node] = Node(a[l]);
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    nodes[node] = combine(nodes[2 * node + 1], nodes[2 * node + 2]);
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(0, n - 1, 0);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r, k;
            cin >> l >> r >> k;
            upd(0, n - 1, 0, l, r, k);
        } else {
            int l, r;
            cin >> l >> r;
            ll first = query(0, n - 1, 0, l, l).sum[0];

            Node node = query(0, n - 1, 0, l, r);
            if (node.pref_mn[0][0] < 1) {
                cout << 0 << endl;
                continue;
            }

            if ((r - l + 1) % 2 == 1 && node.sum[0] != 1) {
                cout << 0 << endl;
                continue;
            }

            if (r > l) {
                node = query(0, n - 1, 0, l + 1, r);
                if (node.pref_mn[0][0] < first) {
                    cout << 0 << endl;
                    continue;
                }
                if ((r - l + 1) % 2 == 0 && node.sum[0] != first) {
                    cout << 0 << endl;
                    continue;
                }
            }
            cout << 1 << endl;
        }
    }

    return 0;
}
