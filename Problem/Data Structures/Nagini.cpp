//https://codeforces.com/contest/855/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int INF = 2e9;

struct Node {
    int mx1[2];
    int mx2[2];
    int mxc[2];
    int setVal[2];

    ll val;
    int ok;

    Node() {
        ok = 0;
        for (int i = 0; i < 2; i++) {
            mx1[i] = INF;
            mx2[i] = -INF;
            mxc[i] = 0;
            setVal[i] = INF;
        }
        val = 0;
    }

};

Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node;
    node.val = left.val + right.val;
    node.ok = left.ok && right.ok;
    for (int i = 0; i < 2; i++) {
        if (left.mx1[i] == right.mx1[i]) {
            node.mx1[i] = left.mx1[i];
            node.mx2[i] = max(left.mx2[i], right.mx2[i]);
            node.mxc[i] = left.mxc[i] + right.mxc[i];
        } else if (left.mx1[i] > right.mx1[i]) {
            node.mx1[i] = left.mx1[i];
            node.mx2[i] = max(left.mx2[i], right.mx1[i]);
            node.mxc[i] = left.mxc[i];
        } else {
            node.mx1[i] = right.mx1[i];
            node.mx2[i] = max(left.mx1[i], right.mx2[i]);
            node.mxc[i] = right.mxc[i];
        }
    }
    return node;
}

void compose(int parent, int child) {
    for (int i = 0; i < 2; i++) {
        segtree[child].setVal[i] = min(segtree[child].setVal[i], segtree[parent].setVal[i]);
    }

}

void apply(int node, int l, int r) {
    for (int i = 0; i < 2; i++) {
        if (segtree[node].setVal[i] < segtree[node].mx1[i]) {
            segtree[node].val -= (ll)segtree[node].mxc[i] * (segtree[node].mx1[i] - segtree[node].setVal[i]);
            segtree[node].mx1[i] = segtree[node].setVal[i];
        }
    }
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    segtree[node].setVal[0] = INF;
    segtree[node].setVal[1] = INF;
}

void setUpdate(int node, int l, int r, int lq, int rq, ll val, int f) {
    apply(node, l, r);
    if (l > rq || lq > r || segtree[node].mx1[f] <= val) {
        return;
    }
    if (l >= lq && r <= rq && segtree[node].mx2[f] < val && segtree[node].mx1[f] != INF) {
        segtree[node].setVal[f] = val;
        return;
    }
    if (l == r) {
        segtree[node].mx1[f] = val;
        if (segtree[node].mx1[0] != INF && segtree[node].mx1[1] != INF) {
            segtree[node].ok = 1;
            segtree[node].mxc[0] = 1;
            segtree[node].mxc[1] = 1;
            segtree[node].val = segtree[node].mx1[0] + segtree[node].mx1[1];
        }
        return;
    }
    int mid = (l + r) / 2;
    setUpdate(node * 2 + 1, l, mid, lq, rq, val, f);
    setUpdate(node * 2 + 2, mid + 1, r, lq, rq, val, f);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}


ll query_sum(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq) {
        return 0;
    }
    apply(node, l, r);
    if (lq <= l && rq >= r) {
        return segtree[node].val;
    }
    int mid = (l + r) / 2;
    return query_sum(l, mid, lq, rq, 2 * node + 1) + query_sum(mid + 1, r, lq, rq, 2 * node + 2);
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node();
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}


int main() {
    IOS;
    int q;
    cin >> q;
    build(0, N - 1, 0);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r, k;
            cin >> l >> r >> k;
            l--, r -= 2;
            int f = 0;
            if (k < 0) {
                f = 1;
                k *= -1;
            }
            setUpdate(0, 0, N - 1, l, r, k, f);
        } else {
            int l, r;
            cin >> l >> r;
            l--, r -= 2;
            cout << query_sum(0, N - 1, l, r, 0) << endl;
        }

    }

    return 0;
}
