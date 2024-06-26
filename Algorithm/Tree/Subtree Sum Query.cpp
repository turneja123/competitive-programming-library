//https://cses.fi/problemset/task/1137
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

list <int> adj[N];

int sz[N];
int tour[N];
int vals[N];
ll a[N];
ll segtree[4 * N];
bool vis[N];

int euler = 0;

int dfs(int v, int ct) {
    tour[v] = euler++;
    vis[v] = true;
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        if (!vis[*it]) {
            ct += dfs(*it, 1);
        }
    }
    return sz[v] = ct;
}

ll rsq(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    if (l > rq || r < lq) {
        return 0;
    }

    int mid = (l + r) / 2;
    return rsq(l, mid, lq, rq, 2 * node + 1) + rsq(mid + 1, r, lq, rq, 2 * node + 2);
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
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = a[l];
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> vals[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 1);
    for (int i = 0; i < n; i++) {
        a[tour[i]] = vals[i];
    }
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            ll s, x;
            cin >> s >> x;
            s--;
            update(0, n - 1, tour[s], x, 0);
        }
        else {
            int s;
            cin >> s;
            s--;
            ll ans = rsq(0, n - 1, tour[s], tour[s] + sz[s] - 1, 0);
            cout << ans << endl;
        }
    }
    return 0;
}
