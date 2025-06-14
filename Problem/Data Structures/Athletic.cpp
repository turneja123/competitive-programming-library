//https://atcoder.jp/contests/abc408/tasks/abc408_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int segtree[4 * N];
int a[N];

int rmq(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    if (l > rq || r < lq) {
        return -N;
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

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = -N;
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = max(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    int n, d, r;
    cin >> n >> d >> r;
    vector<pair<int, int>> sorted;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sorted.push_back(make_pair(a[i], i));
    }
    build(0, n - 1, 0);
    sort(sorted.begin(), sorted.end());
    reverse(sorted.begin(), sorted.end());
    int ans = 1;
    priority_queue<tuple<int, int, int>> pq;
    for (auto [h, i] : sorted) {
        while (pq.size() && h <= get<0>(pq.top()) - d) {
            auto [H, I, DP] = pq.top();
            update(0, n - 1, I, DP, 0);
            pq.pop();
        }
        int dp = max(1, rmq(0, n - 1, max(0, i - r), min(n - 1, i + r), 0) + 1);
        ans = max(ans, dp);
        pq.push(make_tuple(h, i, dp));
    }
    cout << ans - 1;
    return 0;
}
