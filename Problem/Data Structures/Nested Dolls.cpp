//https://www.spoj.com/problems/MDOLLS/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e4 + 5;

pair<int, int> a[N];
int segtree[4 * N];

int rmq(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq || lq > rq) {
        return 0;
    }

    if (lq <= l && rq >= r) {
        return segtree[node];
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
        segtree[node] = 0;
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = max(segtree[2 * node + 1], segtree[2 * node + 2]);
}

bool comp(pair<int, int> x, pair<int, int> y)  {
    if (x.first != y.first) {
        return x.first < y.first;
    }
    return x.second > y.second;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i].first >> a[i].second;
        }
        sort(a, a + n, comp);
        build(0, N - 1, 0);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int cur = 1 + rmq(0, N - 1, a[i].second, N - 1, 0);
            ans = max(ans, cur);
            update(0, N - 1, a[i].second, cur, 0);
        }
        cout << ans << endl;
    }
    return 0;
}
