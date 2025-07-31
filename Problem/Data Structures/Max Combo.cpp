//https://atcoder.jp/contests/abc415/tasks/abc415_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
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

void update(int l, int r, int ind, ll val, int node) {
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
    string s;
    cin >> n >> q >> s;
    a[0] = 0;
    for (int i = 1; i < n; i++) {
        if (s[i] == s[i - 1]) {
            a[i] = 1;
        } else {
            a[i] = -N;
        }
    }
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int j; char x;
            cin >> j >> x;
            j--;
            s[j] = x;
            if (j > 0) {
                if (s[j] == s[j - 1]) {
                    update(0, n - 1, j, 1, 0);
                } else {
                    update(0, n - 1, j, -N, 0);
                }
            }
            if (j < n - 1) {
                if (s[j] == s[j + 1]) {
                    update(0, n - 1, j + 1, 1, 0);
                } else {
                    update(0, n - 1, j + 1, -N, 0);
                }
            }
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            update(0, n - 1, l, 0, 0);
            Node node = query(0, n - 1, l, r, 0);
            cout << node.val + 1 << endl;
            ll x = 0;
            if (l > 0) {
                if (s[l] == s[l - 1]) {
                    x = 1;
                } else {
                    x = -N;
                }
            }
            update(0, n - 1, l, x, 0);
        }
    }
    return 0;
}
