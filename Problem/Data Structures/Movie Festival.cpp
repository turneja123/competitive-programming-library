//https://cses.fi/problemset/task/1629/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 2e9;

pair<int, int> ivals[N];
pair<int, int> segtree[4 * N];

pair<int, int> combine(pair<int, int> a, pair<int, int> b) {
    if (a.first < b.first) {
        return a;
    } else if (a.first > b.first) {
        return b;
    }
    return make_pair(a.first, min(a.second, b.second));
}

pair<int, int> rmq(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    if (l > rq || r < lq) {
        return make_pair(INF, -1);
    }

    int mid = (l + r) / 2;
    return combine(rmq(l, mid, lq, rq, 2 * node + 1), rmq(mid + 1, r, lq, rq, 2 * node + 2));
}

void update(int l, int r, int ind, int val, int node) {
    if (l == r) {
        segtree[node].first = val;
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
        segtree[node] = make_pair(ivals[l].second, l);
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> ivals[i].first >> ivals[i].second;
    }
    sort(ivals, ivals + n);
    build(0, n - 1, 0);
    int ans = 0, i = 0;
    while (i < n) {
        pair<int, int> r = rmq(0, n - 1, i, n - 1, 0);
        if (r.first == INF) {
            break;
        }
        ans++;
        update(0, n - 1, r.second, INF, 0);
        i = lower_bound(ivals, ivals + n, make_pair(r.first, 0)) - ivals;
    }

    cout << ans;
    return 0;
}
