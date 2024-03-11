//solution for https://dmoj.ca/problem/bsfast
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int INF = 2e9;

int a[N];
int segtree[4 * N];

int traverse(int l, int r, int lq, int rq, int node, int k) {
    if (l == r) {
        if (segtree[node] < k) {
            return l;
        } else {
            return INF;
        }
    }

    if (l > rq || r < lq || l > r) {
        return INF;
    }

    int mid = (l + r) / 2;
    if (segtree[2 * node + 1] < k) {
        return traverse(l, mid, lq, rq, 2 * node + 1, k);
    } else {
        return traverse(mid + 1, r, lq, rq, 2 * node + 2, k);
    }
}

int query(int l, int r, int lq, int rq, int node, int k) {
    if (lq <= l && rq >= r) {
        if (segtree[node] < k) {
            return traverse(l, r, lq, rq, node, k);
        } else {
            return INF;
        }
    }

    if (l > rq || r < lq || l > r) {
        return INF;
    }

    int mid = (l + r) / 2;
    int lf = query(l, mid, lq, rq, 2 * node + 1, k);
    if (lf != INF) {
        return lf;
    } else {
        return query(mid + 1, r, lq, rq, 2 * node + 2, k);
    }
}

void update(int l, int r, int ind, int val, int node) {
    if (l == r) {
        a[ind] = val;
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
        segtree[node] = a[l];
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
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(0, n - 1, 0);
    int lastAns = 0;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int ind; int val;
            cin >> ind >> val;
            ind ^= lastAns;
            val ^= lastAns;
            ind--;
            update(0, n - 1, ind, val, 0);
        } else {
            int l, r, k;
            cin >> l >> r >> k;
            l ^= lastAns;
            r ^= lastAns;
            k ^= lastAns;
            l--, r--;
            lastAns = query(0, n - 1, l, r, 0, k) + 1;
            cout << lastAns << endl;
        }
    }

    return 0;
}
