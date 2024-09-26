//https://atcoder.jp/contests/abc165/tasks/abc165_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
pair<int, int> compr[N];
vector<int> adj[N];

int segtree[4 * N];
int ans[N];

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

void dfs(int u, int p, int n) {
    int old = rmq(0, n - 1, a[u], a[u], 0);
    int cur = rmq(0, n - 1, 0, a[u] - 1, 0) + 1;
    update(0, n - 1, a[u], cur, 0);
    ans[u] = rmq(0, n - 1, 0, n - 1, 0);
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, n);
        }
    }
    update(0, n - 1, a[u], old, 0);
}

int main(){
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        compr[i] = make_pair(a[i], i);
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    sort(compr, compr + n);
    int m = 0;
    for (int i = 0; i < n; i++) {
        if (i > 0 && compr[i].first > compr[i - 1].first) {
            m++;
        }
        a[compr[i].second] = m;
    }
    m++;
    dfs(0, 0, n);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
