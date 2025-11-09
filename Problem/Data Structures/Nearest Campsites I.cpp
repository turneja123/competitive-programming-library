//https://cses.fi/problemset/task/3306/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int INF = 1e9;

struct Segtree {
    int segtree[4 * N];
    int rmq(int l, int r, int lq, int rq, int node) {
        if (lq <= l && rq >= r) {
            return segtree[node];
        }

        if (l > rq || r < lq) {
            return INF;
        }

        int mid = (l + r) / 2;
        return min(rmq(l, mid, lq, rq, 2 * node + 1),
                   rmq(mid + 1, r, lq, rq, 2 * node + 2));
    }

    void update(int l, int r, int ind, int val, int node) {
        if (l == r) {
            segtree[node] = min(segtree[node], val);
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
};

int ans[N];
vector<int> add[N];
vector<pair<int, int>> query[N];



int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        add[x].push_back(y);
    }
    for (int i = 0; i < m; i++) {
        ans[i] = INF;
        int x, y;
        cin >> x >> y;
        query[x].push_back({y, i});
    }
    Segtree L, R;
    L.build(0, N - 1, 0);
    R.build(0, N - 1, 0);
    for (int x = 0; x < N; x++) {
        for (auto y : add[x]) {
            L.update(0, N - 1, y, -x - y, 0);
            R.update(0, N - 1, y, -x + y, 0);
        }
        for (auto [y, j] : query[x]) {
            ans[j] = min(ans[j], x + y + L.rmq(0, N - 1, 0, y, 0));
            ans[j] = min(ans[j], x - y + R.rmq(0, N - 1, y, N - 1, 0));
        }
    }
    L.build(0, N - 1, 0);
    R.build(0, N - 1, 0);
    for (int x = N - 1; x >= 0; x--) {
        for (auto y : add[x]) {
            L.update(0, N - 1, y, x - y, 0);
            R.update(0, N - 1, y, x + y, 0);
        }
        for (auto [y, j] : query[x]) {
            ans[j] = min(ans[j], -x + y + L.rmq(0, N - 1, 0, y, 0));
            ans[j] = min(ans[j], -x - y + R.rmq(0, N - 1, y, N - 1, 0));
        }
    }
    int mx = 0;
    for (int i = 0; i < m; i++) {
        mx = max(mx, ans[i]);
    }
    cout << mx << endl;
    return 0;
}
