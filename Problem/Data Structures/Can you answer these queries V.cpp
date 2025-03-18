//https://www.spoj.com/problems/GSS5/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long INF = 1e12;

struct Node {
    long long pref;
    long long suf;
    long long sum;
    long long val;
    Node() : pref(0), suf(0), sum(0), val(0) {}
    Node(long long x) : pref(x), suf(x), sum(x), val(x) {}
};

Node segtree[4 * N];
long long a[N];

Node combine(Node left, Node right) {
    Node node = Node();
    if (left.val == -INF) {
        return right;
    }
    if (right.val == -INF) {
        return left;
    }
    node.sum = left.sum + right.sum;
    node.pref = max(left.pref, left.sum + right.pref);
    node.suf = max(right.suf, right.sum + left.suf);
    node.val = max({left.val, right.val, node.pref, node.suf, left.suf + right.pref});
    return node;
}

Node query(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq) {
        Node sentinel(-INF);
        return sentinel;
    }

    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    int mid = (l + r) / 2;
    return combine(query(l, mid, lq, rq, 2 * node + 1), query(mid + 1, r, lq, rq, 2 * node + 2));
}

void update(int l, int r, int ind, int val, int node) {
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
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        build(0, n - 1, 0);
        cin >> q;
        for (int i = 0; i < q; i++) {
            int lx, rx, ly, ry;
            cin >> lx >> rx >> ly >> ry;
            lx--, rx--, ly--, ry--;
            Node lf = query(0, n - 1, lx, rx, 0), rt = query(0, n - 1, ly, ry, 0);
            if (rx < ly) {
                Node mid = query(0, n - 1, rx + 1, ly - 1, 0);
                cout << lf.suf + (mid.sum == -INF ? 0 : mid.sum) + rt.pref << endl;
                continue;
            }
            Node mid = query(0, n - 1, ly, rx, 0);
            long long ans = mid.val;
            Node left = query(0, n - 1, lx, ly - 1, 0);
            ans = max(ans, left.suf + rt.pref);
            Node right = query(0, n - 1, rx + 1, ry, 0);
            ans = max(ans, lf.suf + right.pref);
            ans = max(ans, lf.suf);
            ans = max(ans, rt.pref);
            cout << ans << endl;
        }
    }

    return 0;
}
