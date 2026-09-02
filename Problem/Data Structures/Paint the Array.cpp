//https://codeforces.com/contest/2237/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const int INF = 1e9;

struct Node {
    bool setValid;
    int setVal;
    int mx;
    Node() {
        setValid = 0;
        setVal = -INF;
        mx = -INF;
    }
    Node(int x) {
        setValid = 0;
        setVal = -INF;
        mx = x;
    }
};

int a[N];
Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.mx = max(left.mx, right.mx);
    return node;
}

void compose(int parent, int child) {
    if (segtree[parent].setValid) {
        segtree[child].setValid = 1;
        segtree[child].setVal = max(segtree[child].setVal, segtree[parent].setVal);
    }
}

void apply(int node, int l, int r) {
    if (segtree[node].setValid) {
        segtree[node].mx = max(segtree[node].mx, segtree[node].setVal);
    }
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    segtree[node].setValid = false;
    segtree[node].setVal = -INF;
}

void setUpdate(int node, int l, int r, int lq, int rq, int val) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].setValid = true;
        segtree[node].setVal = max(segtree[node].setVal, val);
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

void upd(int l, int r, int node, int ind, int f, int val) {
    apply(node, l, r);
    if (l == r) {
        if (f == 0) {
            segtree[node].mx = val;
        } else {
            segtree[node].mx += val;
        }
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        upd(l, mid, 2 * node + 1, ind, f, val);
    } else {
        upd(mid + 1, r, 2 * node + 2, ind, f, val);
    }
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int query(int l, int r, int node, int ind) {
    apply(node, l, r);
    if (l == r) {
        return segtree[node].mx;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        return query(l, mid, 2 * node + 1, ind);
    } else {
        return query(mid + 1, r, 2 * node + 2, ind);
    }
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(-INF);
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}



int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        build(0, n - 1, 0);
        upd(0, n - 1, 0, m - 1, 0, a[0] == 1);
        for (int i = 1; i < n; i++) {
            apply(0, 0, n - 1);
            int dp = segtree[0].mx;
            if (i + m - 1 < n) {
                setUpdate(0, 0, n - 1, i + m - 1, i + m - 1, dp);
            }
            if (i >= m) {
                int dp = query(0, n - 1, 0, i - 1);
                setUpdate(0, 0, n - 1, i, min(n - 1, i + m - 1), dp);
                upd(0, n - 1, 0, i - 1, 0, -INF);
            }
            int j = i - a[i] + m;
            if (max(i, m - 1) <= j && j <= min(n - 1, i + m - 1)) {
                upd(0, n - 1, 0, j, 1, 1);
            }
        }
        cout << n - query(0, n - 1, 0, n - 1) << endl;
    }

    return 0;
}
