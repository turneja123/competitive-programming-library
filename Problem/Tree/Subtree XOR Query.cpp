//https://www.hackerearth.com/challenges/competitive/june-circuits-23/algorithm/subtree-query-cbd6ea30/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int M = 25;

list <int> adj[N];
int sz[N];
int tour[N];
long long vals[N];
long long bits[N][M];
long long a[N][M];
bool vis[N];
int euler = 0;

long long segtree[4 * N][M];
long long lazy[4 * N][M];

int dfs(int v, int ct) {
    tour[v] = euler++;
    vis[v] = true;
    long long j = 1;
    for (int p = 0; p < M && j <= vals[v]; p++) {
        long long c = vals[v] & j;
        if (c != 0) {
            bits[v][p] = 1;

        }
        j *= 2;
    }

    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        if (!vis[*it]) {
            ct += dfs(*it, 1);
        }
    }
    return sz[v] = ct;
}

void compose(int parent, int child, int bit) {
    lazy[child][bit] += lazy[parent][bit];
}

void apply(int node, int l, int r, int bit) {
    if (lazy[node][bit] % 2 == 1) {
        segtree[node][bit] = (r - l + 1) - segtree[node][bit];
    }
    if (l != r) {
        compose(node, 2 * node + 1, bit);
        compose(node, 2 * node + 2, bit);
    }
    lazy[node][bit] = 0;
}

void incUpdate(int node, int l, int r, int lq, int rq, int bit) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        lazy[node][bit] += 1;
        return;
    }
    apply(node, l, r, bit);
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq, bit);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq, bit);
    apply(2 * node + 1, l, mid, bit);
    apply(2 * node + 2, mid + 1, r, bit);
    segtree[node][bit] = segtree[node * 2 + 1][bit] + segtree[node * 2 + 2][bit];
}

long long getSum(int l, int r, int lq, int rq, int node, int bit) {
    if (l > rq || lq > r) {
        return 0;
    }
    apply(node, l, r, bit);
    if (l >= lq && r <= rq) {
        return segtree[node][bit];
    }

    int mid = (l + r) / 2;
    return getSum(l, mid, lq, rq, 2 * node + 1, bit) +
           getSum(mid + 1, r, lq, rq, 2 * node + 2, bit);
}

void build(int l, int r, int node, int bit) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node][bit] = a[l][bit];
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1, bit);
    build(mid + 1, r, node * 2 + 2, bit);
    segtree[node][bit] = segtree[node * 2 + 1][bit] + segtree[node * 2 + 2][bit];
}

int main() {
    IOS;
    int n, q;
    cin >> n;

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
    dfs(0, 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < M; j++) {
            a[tour[i]][j] = bits[i][j];
        }
    }
    for (int j = 0; j < M; j++) {
        build(0, n - 1, 0, j);
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 2) {
            long long u, x;
            cin >> u >> x;
            u--;
            long long j = 1;
            for (int p = 0; p < M && j <= x; p++) {
                long long c = x & j;
                if (c != 0) {
                    incUpdate(0, 0, n - 1, tour[u], tour[u] + sz[u] - 1, p);
                }
                j *= 2;
            }
        } else {
            int u;
            cin >> u;
            u--;
            long long ans = 0, j = 1;
            for (int p = 0; p < M; p++) {
                ans += j * getSum(0, n - 1, tour[u], tour[u] + sz[u] - 1, 0, p);
                j *= 2;
            }
            cout << ans << endl;
        }
    }
    return 0;
}
