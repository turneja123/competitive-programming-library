//https://cses.fi/problemset/task/2206/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 1e9;

int a[N];
int x[N];
int y[N];
int segtree[2][4 * N];


int rmq(int l, int r, int lq, int rq, int node, int n) {
    if (lq <= l && rq >= r) {
        return segtree[n][node];
    }

    if (l > rq || r < lq) {
        return INF;
    }

    int mid = (l + r) / 2;
    return min(rmq(l, mid, lq, rq, 2 * node + 1, n),
               rmq(mid + 1, r, lq, rq, 2 * node + 2, n));
}

void update(int l, int r, int ind, int node) {
    if (l == r) {
        segtree[0][node] = x[l];
        segtree[1][node] = y[l];
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, 2 * node + 2);
    }
    segtree[0][node] = min(segtree[0][2 * node + 1], segtree[0][2 * node + 2]);
    segtree[1][node] = min(segtree[1][2 * node + 1], segtree[1][2 * node + 2]);
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[0][node] = x[l];
        segtree[1][node] = y[l];
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[0][node] = min(segtree[0][2 * node + 1], segtree[0][2 * node + 2]);
    segtree[1][node] = min(segtree[1][2 * node + 1], segtree[1][2 * node + 2]);
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        x[i] = a[i] + i;
        y[i] = a[i] - i;
    }
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int ind; ll val;
            cin >> ind >> val;
            ind--;
            a[ind] = val, x[ind] = val + ind, y[ind] = val - ind;
            update(0, n - 1, ind, 0);
        } else {
            int k;
            cin >> k;
            k--;
            int ans = min({a[k], rmq(0, n - 1, k + 1, n - 1, 0, 0) - k, rmq(0, n - 1, 0, k - 1, 0, 1) + k});
            cout << ans << endl;
        }
    }

    return 0;
}
