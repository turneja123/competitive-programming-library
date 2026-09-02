//https://atcoder.jp/contests/abc468/tasks/abc468_f
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
    int val;
    int lazy;
    Node() {
        lazy = 0;
        val = -INF;
    }
    Node(int x) {
        val = x;
        lazy = 0;
    }
};

int a[N];
Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.val = max(left.val, right.val);
    return node;
}

void compose(int parent, int child) {
    segtree[child].lazy += segtree[parent].lazy;
}

void apply(int node, int l, int r) {
    segtree[node].val += segtree[node].lazy;
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

void setUpdate(int node, int l, int r, int ind, int val) {
    apply(node, l, r);
    if (l == r) {
        segtree[node] = Node(val);
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        setUpdate(2 * node + 1, l, mid, ind, val);
    } else {
        setUpdate(2 * node + 2, mid + 1, r, ind, val);
    }
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int getSum(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return -INF;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node].val;
    }
    int mid = (l + r) / 2;
    return max(getSum(l, mid, lq, rq, 2 * node + 1), getSum(mid + 1, r, lq, rq, 2 * node + 2));
}



int main() {
    IOS;
    int n;
    cin >> n;
    setUpdate(0, 0, n, 0, 0);
    int ans = 0, mx = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        if (a > mx) {
            incUpdate(0, 0, n, 0, n, 1);
            ans++;
            setUpdate(0, 0, n, a, ans);
            mx = a;
        } else {
            int x = getSum(0, n, 0, a - 1, 0) + 1;
            ans = max(ans, x);
            setUpdate(0, 0, n, a, x);
        }
    }
    cout << ans;
    return 0;
}
