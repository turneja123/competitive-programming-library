//https://codeforces.com/contest/522/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int a[N];
int rt[N];
int val[N];
int last[N];
pair<int, int> compr[N];
int ans[N];

tuple<int, int, int> queries[N];

const int INF = 1e9;

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

void update(int l, int r, int ind, ll val, int node) {
    if (l == r) {
        a[ind] = val;
        segtree[node] = val;
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

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        compr[i] = make_pair(a[i], i);
    }
    sort(compr, compr + n);
    int m = 0;
    for (int i = 0; i < n; i++) {
        if (i > 0 && compr[i].first > compr[i - 1].first) {
            m++;
        }
        val[m] = a[compr[i].second];
        a[compr[i].second] = m;
    }
    m++;
    for (int i = 0; i < m; i++) {
        last[i] = INF;
    }
    for (int i = n - 1; i >= 0; i--) {
        rt[i] = last[a[i]];
        last[a[i]] = i;
    }
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        queries[i] = make_tuple(l, r, i);
    }
    sort(queries, queries + q, greater<tuple<int, int, int>>());
    build(0, n - 1, 0);
    for (int i = 0, j = n - 1; i < q; i++) {
        int l = get<0>(queries[i]), r = get<1>(queries[i]), cur = get<2>(queries[i]);
        while (j >= l) {
            if (rt[j] < n) {
                update(0, n - 1, rt[j], rt[j] - j, 0);
            }
            j--;
        }
        int d = rmq(0, n - 1, l, r, 0);
        if (d < n) {
            ans[cur] = d;
        } else {
            ans[cur] = -1;
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
