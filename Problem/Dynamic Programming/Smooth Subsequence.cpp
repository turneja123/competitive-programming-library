//https://atcoder.jp/contests/abc339/tasks/abc339_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int a[N];
int dp[N];
int segtree[4 * N];

int rmq(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    if (l > rq || r < lq) {
        return 0;
    }

    int mid = (l + r) / 2;
    return max(rmq(l, mid, lq, rq, 2 * node + 1),
               rmq(mid + 1, r, lq, rq, 2 * node + 2));
}

void update(int l, int r, int ind, int val, int node) {
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
    segtree[node] = max(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    int n, d, mx = 0;
    cin >> n >> d;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mx = max(mx, a[i]);
    }
    for (int i = 0; i < n; i++) {
        dp[a[i]] = max(dp[a[i]], rmq(0, mx, max(0, a[i] - d), min(mx, a[i] + d), 0) + 1);
        dp[a[i]] = max(dp[a[i]], 1);
        update(0, mx, a[i], dp[a[i]], 0);
    }
    int ans = 0;
    for (int i = 1; i <= mx; i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;


    return 0;
}
