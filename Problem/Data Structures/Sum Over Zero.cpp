//https://codeforces.com/contest/1788/problem/E
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
int segtree[4 * N];

int rmq(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    if (l > rq || r < lq) {
        return -INF;
    }

    int mid = (l + r) / 2;
    return max(rmq(l, mid, lq, rq, 2 * node + 1),
               rmq(mid + 1, r, lq, rq, 2 * node + 2));
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
    segtree[node] = max(segtree[2 * node + 1], segtree[2 * node + 2]);
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = -INF;
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = max(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    int n; ll s = 0;
    cin >> n;
    vector<ll> compr{0};
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        s += a[i];
        compr.push_back(s);
    }
    sort(compr.begin(), compr.end());
    compr.erase(unique(compr.begin(), compr.end()), compr.end());
    int m = compr.size();

    auto get = [&](ll s) -> int {
        return lower_bound(compr.begin(), compr.end(), s) - compr.begin();
    };
    build(0, m - 1, 0);
    update(0, m - 1, get(0), 0, 0);
    int ans = 0; s = 0;
    for (int i = 0; i < n; i++) {
        s += a[i];
        int cur = i + 1 + rmq(0, m - 1, 0, get(s), 0);
        ans = max(ans, cur);
        update(0, m - 1, get(s), ans - (i + 1), 0);
    }
    cout << ans;

    return 0;
}
