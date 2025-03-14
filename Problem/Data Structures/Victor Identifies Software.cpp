//https://dmoj.ca/problem/dmopc20c1p6
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const long long INF = 1e18;

struct Node {
    int lazy_flag;
    long long lazy_set;
    bool setValid;
    bool sentinel;

    long long pref[3];
    long long suf[3];
    long long sum[3];
    long long val[3];

    long long pref_ct[3];
    long long suf_ct[3];
    long long sum_ct[3];
    long long val_ct[3];

    Node() {
        lazy_flag = 0;
        lazy_set = 0;
        setValid = false;

        sentinel = true;
        pref[0] = -INF, pref[1] = -INF, pref[2] = -INF;
        suf[0] = -INF, suf[1] = -INF, suf[2] = -INF;
        sum[0] = -INF, sum[1] = -INF, sum[2] = -INF;
        val[0] = -INF, val[1] = -INF, val[2] = -INF;

        pref_ct[0] = -INF, pref_ct[1] = -INF, pref_ct[2] = -INF;
        suf_ct[0] = -INF, suf_ct[1] = -INF, suf_ct[2] = -INF;
        sum_ct[0] = -INF, sum_ct[1] = -INF, sum_ct[2] = -INF;
        val_ct[0] = -INF, val_ct[1] = -INF, val_ct[2] = -INF;
    }
    Node(long long x) {
        lazy_flag = 0;
        lazy_set = 0;
        setValid = false;

        sentinel = false;
        pref[0] = x, pref[1] = -INF, pref[2] = x;
        suf[0] = x, suf[1] = -INF, suf[2] = x;
        sum[0] = x, sum[1] = -INF, sum[2] = x;
        val[0] = x, val[1] = -INF, val[2] = x;

        pref_ct[0] = 1, pref_ct[1] = -INF, pref_ct[2] = 1;
        suf_ct[0] = 1, suf_ct[1] = -INF, suf_ct[2] = 1;
        sum_ct[0] = 1, sum_ct[1] = -INF, sum_ct[2] = 1;
        val_ct[0] = 1, val_ct[1] = -INF, val_ct[2] = 1;

    }
};

Node segtree[4 * N];
long long a[N];

long long add(long long a, long long b) {
    if (a == -INF) {
        return -INF;
    }
    if (b == -INF) {
        return -INF;
    }
    return a + b;
}

Node combine(Node left, Node right) {
    Node node = Node();
    if (left.sentinel) {
        return right;
    }
    if (right.sentinel) {
        return left;
    }
    node.sentinel = false;
    for (int i = 0; i < 3; i++) {
        node.sum[i] = max(-INF, add(left.sum[i], right.sum[i]));
        node.pref[i] = max(left.pref[i], add(left.sum[i], right.pref[i]));
        node.suf[i] = max(right.suf[i], add(right.sum[i], left.suf[i]));
        node.val[i] = max({left.val[i], right.val[i], node.pref[i], node.suf[i], add(left.suf[i], right.pref[i])});

        node.sum_ct[i] = max(-INF, add(left.sum_ct[i], right.sum_ct[i]));
        node.pref_ct[i] = max(left.pref_ct[i], add(left.sum_ct[i], right.pref_ct[i]));
        node.suf_ct[i] = max(right.suf_ct[i], add(right.sum_ct[i], left.suf_ct[i]));
        node.val_ct[i] = max({left.val_ct[i], right.val_ct[i], node.pref_ct[i], node.suf_ct[i], add(left.suf_ct[i], right.pref_ct[i])});
    }
    return node;
}

void compose(int parent, int child) {
    if (segtree[parent].setValid) {
        segtree[child].setValid = 1;
        segtree[child].lazy_set = segtree[parent].lazy_set;
    }
    if (segtree[parent].lazy_flag != 0) {
        segtree[child].lazy_flag = segtree[parent].lazy_flag;
    }
}

void apply(int node, int l, int r) {
    if (segtree[node].setValid) {
        long long x = segtree[node].lazy_set;
        if (x >= 0) {
            segtree[node].pref[0] = (segtree[node].pref_ct[0] == -INF ? -INF : segtree[node].pref_ct[0] * x);
            segtree[node].pref[1] = (segtree[node].pref_ct[1] == -INF ? -INF : segtree[node].pref_ct[1] * x);
            segtree[node].pref[2] = x * (r - l + 1);

            segtree[node].suf[0] = (segtree[node].suf_ct[0] == -INF ? -INF : segtree[node].suf_ct[0] * x);
            segtree[node].suf[1] = (segtree[node].suf_ct[1] == -INF ? -INF : segtree[node].suf_ct[1] * x);
            segtree[node].suf[2] = x * (r - l + 1);

            segtree[node].sum[0] = (segtree[node].sum_ct[0] == -INF ? -INF : segtree[node].sum_ct[0] * x);
            segtree[node].sum[1] = (segtree[node].sum_ct[1] == -INF ? -INF : segtree[node].sum_ct[1] * x);
            segtree[node].sum[2] = x * (r - l + 1);

            segtree[node].val[0] = (segtree[node].val_ct[0] == -INF ? -INF : segtree[node].val_ct[0] * x);
            segtree[node].val[1] = (segtree[node].val_ct[1] == -INF ? -INF : segtree[node].val_ct[1] * x);
            segtree[node].val[2] = x * (r - l + 1);
        } else {
            segtree[node].pref[0] = (segtree[node].pref_ct[0] == -INF ? -INF : x);
            segtree[node].pref[1] = (segtree[node].pref_ct[1] == -INF ? -INF : x);
            segtree[node].pref[2] = x;

            segtree[node].suf[0] = (segtree[node].suf_ct[0] == -INF ? -INF : x);
            segtree[node].suf[1] = (segtree[node].suf_ct[1] == -INF ? -INF : x);
            segtree[node].suf[2] = x;

            segtree[node].sum[0] = (segtree[node].sum_ct[0] == -INF ? -INF : segtree[node].sum_ct[0] * x);
            segtree[node].sum[1] = (segtree[node].sum_ct[1] == -INF ? -INF : segtree[node].sum_ct[1] * x);
            segtree[node].sum[2] = x * (r - l + 1);

            segtree[node].val[0] = (segtree[node].val_ct[0] == -INF ? -INF : x);
            segtree[node].val[1] = (segtree[node].val_ct[1] == -INF ? -INF : x);
            segtree[node].val[2] = x;
        }
    }
    if (segtree[node].lazy_flag == 1) {
        segtree[node].pref[1] = -INF, segtree[node].pref_ct[1] = -INF;
        segtree[node].suf[1] = -INF, segtree[node].suf_ct[1] = -INF;
        segtree[node].sum[1] = -INF, segtree[node].sum_ct[1] = -INF;
        segtree[node].val[1] = -INF, segtree[node].val_ct[1] = -INF;

        segtree[node].pref[0] = segtree[node].pref[2], segtree[node].pref_ct[0] = segtree[node].pref_ct[2];
        segtree[node].suf[0] = segtree[node].suf[2], segtree[node].suf_ct[0] = segtree[node].suf_ct[2];
        segtree[node].sum[0] = segtree[node].sum[2], segtree[node].sum_ct[0] = segtree[node].sum_ct[2];
        segtree[node].val[0] = segtree[node].val[2], segtree[node].val_ct[0] = segtree[node].val_ct[2];
    } else if (segtree[node].lazy_flag == 2) {
        segtree[node].pref[0] = -INF, segtree[node].pref_ct[0] = -INF;
        segtree[node].suf[0] = -INF, segtree[node].suf_ct[0] = -INF;
        segtree[node].sum[0] = -INF, segtree[node].sum_ct[0] = -INF;
        segtree[node].val[0] = -INF, segtree[node].val_ct[0] = -INF;

        segtree[node].pref[1] = segtree[node].pref[2], segtree[node].pref_ct[1] = segtree[node].pref_ct[2];
        segtree[node].suf[1] = segtree[node].suf[2], segtree[node].suf_ct[1] = segtree[node].suf_ct[2];
        segtree[node].sum[1] = segtree[node].sum[2], segtree[node].sum_ct[1] = segtree[node].sum_ct[2];
        segtree[node].val[1] = segtree[node].val[2], segtree[node].val_ct[1] = segtree[node].val_ct[2];
    }

    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    segtree[node].setValid = false;
    segtree[node].lazy_set = 0;
    segtree[node].lazy_flag = 0;
}

void setUpdate(int node, int l, int r, int lq, int rq, long long val) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].setValid = true;
        segtree[node].lazy_set = val;
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

void flagUpdate(int node, int l, int r, int lq, int rq, int val) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].lazy_flag = val;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    flagUpdate(node * 2 + 1, l, mid, lq, rq, val);
    flagUpdate(node * 2 + 2, mid + 1, r, lq, rq, val);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}


Node query(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq) {
        Node sentinel = Node();
        return sentinel;
    }
    apply(node, l, r);
    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    int mid = (l + r) / 2;
    return combine(query(l, mid, lq, rq, 2 * node + 1), query(mid + 1, r, lq, rq, 2 * node + 2));
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
        if (t == 1 || t == 2) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            flagUpdate(0, 0, n - 1, l, r, t);
        } else if (t == 3) {
            int l, r; long long x;
            cin >> l >> r >> x;
            l--, r--;
            setUpdate(0, 0, n - 1, l, r, x);
        } else {
            t -= 4;
            int l, r;
            cin >> l >> r;
            l--, r--;
            Node node = query(0, n - 1, l, r, 0);
            if (node.val_ct[t] == -INF) {
                cout << "breaks galore" << endl;
            } else {
                cout << node.val[t] << endl;
            }

        }
    }

    return 0;
}
