//https://codeforces.com/contest/2057/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long INF = 1e16;

struct Node {
    long long yr;
    long long xl;
    long long yl;
    long long xr;
    long long val;
    Node() : yr(0), xl(0), yl(0), xr(0), val(0) {}
    Node(long long yr, long long xl, long long yl, long long xr) : yr(yr), xl(xl), yl(yl), xr(xr), val(0) {}
};

Node segtree[4 * N];
long long a[N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.yr = max(left.yr, right.yr);
    node.xl = min(left.xl, right.xl);
    node.yl = max(left.yl, right.yl);
    node.xr = min(left.xr, right.xr);
    node.val = max({left.val, right.val, right.yr - left.xl, left.yl - right.xr});
    return node;
}

void update(int l, int r, int ind, int val, int node) {
    if (l == r) {
        segtree[node] = Node(val - r, val - l, val + l, val + r);
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
        segtree[node] = Node(a[l] - r, a[l] - l, a[l] + l, a[l] + r);
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
        cin >> n >> q;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        build(0, n - 1, 0);
        cout << segtree[0].val << endl;
        for (int i = 0; i < q; i++) {
            int j, val;
            cin >> j >> val;
            j--;
            update(0, n - 1, j, val, 0);
            cout << segtree[0].val << endl;
        }
    }
    return 0;
}
