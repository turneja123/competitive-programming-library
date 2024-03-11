//solution for https://www.spoj.com/problems/HBD/
#pragma GCC target ("avx2")
#pragma GCC optimization ("Ofast")
#pragma GCC optimization ("unroll-loops")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

list<int> adj[N];
int up[N][18];

int sz[N];
int tour[N];
int depth[N];

ll vals[N];
ll sums[N];
ll a[N];
bool vis[N];
int euler = 0, timer = 0, lg;

ll segtree[4 * N];
ll lazy[4 * N];

int dfs(int v, int ct, int p) {
    tour[v] = euler++;
    sums[v] += vals[v];
    vis[v] = true;
    up[v][0] = p;
    for (int i = 1; i <= lg; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        if (!vis[*it]) {
            sums[*it] += sums[v];
            depth[*it] = depth[v] + 1;
            ct += dfs(*it, 1, v);
        }
    }
    return sz[v] = ct;
}

int kth(int v, int k) {
    while (k > 0) {
        int l = log2(k);
        v = up[v][l];
        k ^= 1 << l;
    }
    return v;
}

void compose(int parent, int child) {
    lazy[child] += lazy[parent];
}

void apply(int node, int l, int r) {
    segtree[node] += (r - l + 1) * lazy[node];
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    lazy[node] = 0;
}

void incUpdate(int node, int l, int r, int lq, int rq, ll add) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        lazy[node] += add;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq, add);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = segtree[node * 2 + 1] + segtree[node * 2 + 2];
}

ll getSum(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return 0;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node];
    }

    int mid = (l + r) / 2;
    return getSum(l, mid, lq, rq, 2 * node + 1) +
           getSum(mid + 1, r, lq, rq, 2 * node + 2);
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
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = segtree[node * 2 + 1] + segtree[node * 2 + 2];
}

int bin(int u, int v, ll x, int n) {
    int l = 0;
    int r = depth[v] - depth[u];
    int mn = N;
    ll sumv = getSum(0, n - 1, tour[v], tour[v], 0);
    ll sumu = getSum(0, n - 1, tour[u], tour[u], 0);
    if (sumv - sumu + vals[u] < x) {
        return mn;
    }
    while (l <= r) {
        int mid = (l + r) / 2;
        int k = kth(v, mid);
        ll sum = sumv - getSum(0, n - 1, tour[k], tour[k], 0) + vals[k];
        if (sum >= x) {
            mn = min(mn, mid);
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return mn;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    lg = ceil(log2(n));
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        cin >> vals[i];
    }
    dfs(0, 1, 0);
    for (int i = 0; i < n; i++) {
        a[tour[i]] = sums[i];
    }
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 2) {
            ll s, x;
            cin >> s >> x;
            s--;
            incUpdate(0, 0, n - 1, tour[s], tour[s] + sz[s] - 1,  x);
            vals[s] += x;
        } else {
            ll u, v, x;
            cin >> u >> v >> x;
            u--, v--;

            int ct = bin(u, v, x, n);
            if (ct == N) {
                cout << -1 << endl;
            } else {
                cout << ct + 1 << endl;
            }
        }
    }
    return 0;
}
