//https://atcoder.jp/contests/abc353/tasks/abc353_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;
const long long INF = 3e18;

ll segtree[2][4 * N];
long long dp[N];

ll rmq(int l, int r, int lq, int rq, int node, int n) {
    if (lq <= l && rq >= r) {
        return segtree[n][node];
    }

    if (l > rq || r < lq) {
        return -INF;
    }

    int mid = (l + r) / 2;
    return max(rmq(l, mid, lq, rq, 2 * node + 1, n),
               rmq(mid + 1, r, lq, rq, 2 * node + 2, n));
}

void update(int l, int r, int ind, ll val, int node, int n) {
    if (l == r) {
        segtree[n][node] = val;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1, n);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2, n);
    }
    segtree[n][node] = max(segtree[n][2 * node + 1], segtree[n][2 * node + 2]);
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[0][node] = -INF;
        segtree[1][node] = -INF;
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[0][node] = max(segtree[0][2 * node + 1], segtree[0][2 * node + 2]);
    segtree[1][node] = max(segtree[1][2 * node + 1], segtree[1][2 * node + 2]);
}

int main() {
    IOS;
    int n, m; long long c;
    cin >> n >> c >> m;
    for (int i = 0; i < n; i++) {
        dp[i] = -INF;
    }
    build(0, n - 1, 0);
    dp[0] = 0;
    update(0, n - 1, 0, 0, 0, 0);
    long long ans = 0;
    for (int i = 0; i < m; i++) {
        int j; long long k;
        cin >> j >> k;
        j--;
        long long best = max(rmq(0, n - 1, 0, j, 0, 0) - c * j + k, rmq(0, n - 1, j, n - 1, 0, 1) + c * j + k);
        if (dp[j] < best) {
            dp[j] = best;
            ans = max(ans, dp[j]);
            update(0, n - 1, j, dp[j] + c * j, 0, 0);
            update(0, n - 1, j, dp[j] - c * j, 0, 1);
        }
    }
    cout << ans;
    return 0;
}
