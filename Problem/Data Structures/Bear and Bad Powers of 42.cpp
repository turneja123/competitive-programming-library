//https://codeforces.com/contest/679/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

ll pw[11];
int a[N];

ll dist(ll x) {
    int j = upper_bound(pw, pw + 11, x) - pw;
    return pw[j] - x;
}

struct Node {
    int uniform;
    ll lazy;
    ll setVal;
    ll mn;
    ll val;
    Node() {
        lazy = 0;
        setVal = -1;
    }
    Node(ll _val) {
        lazy = 0;
        setVal = -1;
        uniform = 1;
        val = _val;
        mn = dist(val);

    }
};

Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node;
    node.mn = min(left.mn, right.mn);
    node.val = left.val;
    node.uniform = left.uniform && right.uniform && left.val == right.val;
    return node;
}

void compose(int parent, int child) {
    if (segtree[parent].setVal != -1) {
        segtree[child].setVal = segtree[parent].setVal;
        segtree[child].lazy = segtree[parent].lazy;
    } else {
        segtree[child].lazy += segtree[parent].lazy;
    }
}

void apply(int node, int l, int r) {
    if (segtree[node].setVal != -1) {
        segtree[node].uniform = 1;
        segtree[node].val = segtree[node].setVal;
        segtree[node].mn = dist(segtree[node].val);
    }
    segtree[node].val += segtree[node].lazy;
    if (segtree[node].uniform) {
        segtree[node].mn = dist(segtree[node].val);
    } else {
        segtree[node].mn -= segtree[node].lazy;
    }
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    segtree[node].lazy = 0;
    segtree[node].setVal = -1;
}

void setUpdate(int node, int l, int r, int lq, int rq, ll val) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].setVal = val;
        segtree[node].lazy = 0;
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

int repa = 0;

void incUpdate(int node, int l, int r, int lq, int rq, ll add) {
    if (l > rq || lq > r) {
        return;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq && segtree[node].mn > add) {
        segtree[node].lazy += add;
        return;
    }
    if (l >= lq && r <= rq && segtree[node].uniform) {
        segtree[node].val += add;
        int j = upper_bound(pw, pw + 11, segtree[node].val) - pw;
        segtree[node].mn = pw[j] - segtree[node].val;
        if (pw[j - 1] == segtree[node].val) {
            repa = 1;
        }
        if (l != r) {
            segtree[2 * node + 1].setVal = segtree[node].val;
            segtree[2 * node + 1].lazy = 0;
            segtree[2 * node + 2].setVal = segtree[node].val;
            segtree[2 * node + 2].lazy = 0;
        }
        return;
    }
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq, add);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

ll query(int l, int r, int ind, int node) {
    apply(node, l, r);
    if (l == r) {
        return segtree[node].val;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        return query(l, mid, ind, 2 * node + 1);
    } else {
        return query(mid + 1, r, ind, 2 * node + 2);
    }
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
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}


int main() {
    IOS;
    pw[0] = 1;
    for (int i = 1; i < 11; i++) {
        pw[i] = pw[i - 1] * 42;
    }
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
            int j;
            cin >> j;
            j--;
            cout << query(0, n - 1, j, 0) << endl;
        } else if (t == 2) {
            int l, r, x;
            cin >> l >> r >> x;
            l--, r--;
            setUpdate(0, 0, n - 1, l, r, x);
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            l--, r--;
            while (1) {
                repa = 0;
                incUpdate(0, 0, n - 1, l, r, x);
                if (!repa) {
                    break;
                }
            }
        }

    }

    return 0;
}
