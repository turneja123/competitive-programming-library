//https://atcoder.jp/contests/abc369/tasks/abc369_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

pair<int, int> coins[N];
pair<int, int> segtree[4 * N];
int ans[N];
int parent[N];

pair<int, int> combine(pair<int, int> a, pair<int, int> b) {
    if (a.first > b.first) {
        return a;
    } else if (a.first < b.first) {
        return b;
    }
    return make_pair(a.first, min(a.second, b.second));
}

pair<int, int> rmq(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    if (l > rq || r < lq) {
        return make_pair(-1, -1);
    }

    int mid = (l + r) / 2;
    return combine(rmq(l, mid, lq, rq, 2 * node + 1), rmq(mid + 1, r, lq, rq, 2 * node + 2));
}

void update(int l, int r, int ind, pair<int, int> val, int node) {
    if (l == r) {
        if (segtree[node].first < val.first) {
            segtree[node] = val;
        }
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
        segtree[node] = make_pair(-1, -1);
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    int h, w, n;
    cin >> h >> w >> n;
    for (int i = 1; i <= n; i++) {
        cin >> coins[i].first >> coins[i].second;
        coins[i].first--, coins[i].second--;
    }
    sort(coins, coins + n + 1);
    update(0, w - 1, 0, make_pair(0, 0), 0);
    int mx = 0, best = -1;
    for (int i = 1; i <= n; i++) {
        pair<int, int> q = rmq(0, w - 1, 0, coins[i].second, 0);
        ans[i] = 1 + q.first, parent[i] = q.second;
        update(0, w - 1, coins[i].second, make_pair(ans[i], i), 0);
        if (ans[i] > mx) {
            mx = ans[i];
            best = i;
        }
    }
    cout << mx << endl;
    string s = "";
    for (int i = 0; i < w - 1 - coins[best].second; i++) {
        s += 'R';
    }
    for (int i = 0; i < h - 1 - coins[best].first; i++) {
        s += 'D';
    }
    while (best != 0) {
        pair<int, int> p = coins[parent[best]];
        for (int i = 0; i < coins[best].second - p.second; i++) {
            s += 'R';
        }
        for (int i = 0; i < coins[best].first - p.first; i++) {
            s += 'D';
        }
        best = parent[best];
    }
    reverse(s.begin(), s.end());
    cout << s;
    return 0;
}
