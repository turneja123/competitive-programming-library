//https://codeforces.com/gym/105698/problem/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int segtree[4 * N];

int spl = -1;

void go(int l, int r, int k, int node) {
    if (l == r) {
        spl = l;
        return;
    }
    int mid = (l + r) / 2;
    if (segtree[2 * node + 2] < k) {
        go(mid + 1, r, k, 2 * node + 2);
    } else {
        go(l, mid, k, 2 * node + 1);
    }
}

void rmq(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq || spl != -1) {
        return;
    }

    if (lq <= l && rq >= r) {
        if (segtree[node] < rq) {
            go(l, r, rq, node);
        }

        return;
    }

    int mid = (l + r) / 2;
    rmq(mid + 1, r, lq, rq, 2 * node + 2);
    rmq(l, mid, lq, rq, 2 * node + 1);
}

void update(int l, int r, int ind, int val, int node) {
    if (l == r) {
        segtree[node] = max(segtree[node], val);
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
        segtree[node] = -1;
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
        int t;
        cin >> t;
        if (t == 1) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            update(0, n - 1, l, r, 0);
        } else {
            int j;
            cin >> j;
            j--;
            spl = -1;
            rmq(0, n - 1, 0, j, 0);
            cout << j - spl + 1 << endl;
        }
    }
    return 0;
}
