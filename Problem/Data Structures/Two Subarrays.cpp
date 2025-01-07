//https://codeforces.com/contest/2042/problem/F
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
    long long pref[2];
    long long suf[2];
    long long sum;
    long long val[2];
    long long a;
    long long b;
    long long prefsuf;
    bool sentinel;
    Node() {}
    Node(long long _a, long long _b) {
        a = _a;
        b = _b;
        if (a == -INF) {
            sentinel = true;
        } else {
            sentinel = false;
        }
        val[0] = a + 2 * b;
        pref[0] = a + b;
        suf[0] = a + b;
        pref[1] = -INF;
        suf[1] = -INF;
        val[1] = -INF;
        prefsuf = -INF;
        sum = a;
    }
};

Node segtree[4 * N];
long long a[N];
long long b[N];

Node combine(Node left, Node right) {
    Node node = Node();
    if (left.sentinel) {
        return right;
    }
    if (right.sentinel) {
        return left;
    }
    node.sentinel = false;
    node.sum = left.sum + right.sum;
    node.pref[0] = max(left.pref[0], left.sum + right.pref[0]);
    node.suf[0] = max(right.suf[0], right.sum + left.suf[0]);
    node.val[0] = max({left.val[0], right.val[0], left.suf[0] + right.pref[0]});
    node.prefsuf = max({left.pref[0] + right.suf[0], left.sum + right.prefsuf, left.prefsuf + right.sum});
    node.pref[1] = max({left.pref[1], left.sum + right.pref[1], left.pref[0] + right.val[0], left.prefsuf + right.pref[0]});
    node.suf[1] = max({right.suf[1], right.sum + left.suf[1], right.suf[0] + left.val[0], left.suf[0] + right.prefsuf});
    node.val[1] = max({left.val[1], right.val[1], left.suf[1] + right.pref[0], left.suf[0] + right.pref[1], left.val[0] + right.val[0]});
    return node;
}

Node query(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq) {
        Node sentinel(-INF, -INF);
        return sentinel;
    }

    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    int mid = (l + r) / 2;
    return combine(query(l, mid, lq, rq, 2 * node + 1), query(mid + 1, r, lq, rq, 2 * node + 2));
}

void update(int l, int r, int ind, int val, int node, int f) {
    if (l == r) {
        if (f == 1) {
            long long a = val, b = segtree[node].b;
            segtree[node] = Node(a, b);
        } else {
            long long a = segtree[node].a, b = val;
            segtree[node] = Node(a, b);
        }
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1, f);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2, f);
    }
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(a[l], b[l]);
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
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    build(0, n - 1, 0);
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1 ||t == 2) {
            int j, val;
            cin >> j >> val;
            j--;
            update(0, n - 1, j, val, 0, t);
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            Node node = query(0, n - 1, l, r, 0);
            cout << node.val[1] << endl;
        }
    }

    return 0;
}
