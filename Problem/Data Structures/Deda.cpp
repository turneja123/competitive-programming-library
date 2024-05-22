//https://dmoj.ca/problem/coci17c1p5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 2e9;

int segtree[4 * N];
int ans;

void traverse(int l, int r, int node, int x) {
    if (l == r) {
        ans = min(ans, l);
        return;
    }
    int mid = (l + r) / 2;
    if (segtree[2 * node + 1] <= x) {
        traverse(l, mid, 2 * node + 1, x);
    } else {
        traverse(mid + 1, r, 2 * node + 2, x);
    }
    return;
}

int rmq(int l, int r, int lq, int rq, int node, int x) {
    if (lq <= l && rq >= r) {
        if (segtree[node] > x) {
            return INF;
        }
        if (ans == INF) {
            traverse(l, r, node, x);
        }
        return segtree[node];
    }

    if (l > rq || r < lq) {
        return INF;
    }

    int mid = (l + r) / 2;
    int lmin = rmq(l, mid, lq, rq, 2 * node + 1, x), rmin = INF;
    if (lmin > x) {
        rmin = rmq(mid + 1, r, lq, rq, 2 * node + 2, x);
    }
    return min(lmin, rmin);
}

void update(int l, int r, int ind, ll val, int node) {
    if (l == r) {
        segtree[node] = val;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2);
    }
    segtree[node] = min(segtree[2 * node + 1], segtree[2 * node + 2]);
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = INF;
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = min(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        char c;
        cin >> c;
        if (c == 'M') {
            int x, j;
            cin >> x >> j;
            j--;
            update(0, n - 1, j, x, 0);
        } else {
            int x, l;
            cin >> x >> l;
            l--;
            ans = INF;
            rmq(0, n - 1, l, n - 1, 0, x);
            cout << ((ans == INF) ? -1 : ans + 1) << endl;
        }
    }

    return 0;
}
