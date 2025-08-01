//https://www.spoj.com/problems/VZLA2019L/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll INF = 1e18;

ll pref[N];
ll t[N];
ll d[N];

struct Node {
    ll bestl;
    ll bestr;
    ll best;
    Node() {
    }
};

Node segtree[4 * N];
long long a[N];

Node combine(Node left, Node right) {
    Node node = Node();
    if (left.bestl == -INF) {
        return right;
    }
    if (right.bestl == -INF) {
        return left;
    }
    node.bestl = max(left.bestl, right.bestl);
    node.bestr = max(left.bestr, right.bestr);
    node.best = max({left.best, right.best, left.bestl + right.bestr});
    return node;
}

Node query(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq) {
        Node sentinel;
        sentinel.bestl = -INF;
        return sentinel;
    }

    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    int mid = (l + r) / 2;
    return combine(query(l, mid, lq, rq, 2 * node + 1), query(mid + 1, r, lq, rq, 2 * node + 2));
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node();
        ll p = pref[l] - t[l];
        segtree[node].bestl = d[l] - p;
        segtree[node].bestr = d[l] + p;
        segtree[node].best = -INF;
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> t[i];
        t[i + n] = t[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> d[i];
        d[i] *= 2;
        d[i + n] = d[i];
    }
    for (int i = 0; i < 2 * n; i++) {
        pref[i] = (i == 0 ? 0 : pref[i - 1]) + t[i];
    }
    build(0, 2 * n - 1, 0);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        if (l <= r) {
            Node L, R;
            ll ans = -INF;
            if (l > 0) {
                L = query(0, 2 * n - 1, n, n + l - 1, 0);
                ans = max(ans, L.best);
            }
            if (r < n - 1) {
                R = query(0, 2 * n - 1, r + 1, n - 1, 0);
                ans = max(ans, R.best);
            }
            if (l > 0 && r < n - 1) {
                Node node = combine(R, L);
                ans = max(ans, node.best);
            }
            cout << ans << endl;
        } else {
            Node node = query(0, 2 * n - 1, r + 1, l - 1, 0);
            cout << node.best << endl;
        }
    }
    return 0;
}
