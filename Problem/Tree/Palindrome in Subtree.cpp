//https://www.spoj.com/problems/PLNDTREE/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

list <int> adj[N];

int sz[N];
int tour[N];
string a, vals;
int segtree[26][4 * N];
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

int rsq(int l, int r, int lq, int rq, int node, int n) {
    if (lq <= l && rq >= r) {
        return segtree[n][node];
    }

    if (l > rq || r < lq) {
        return 0;
    }

    int mid = (l + r) / 2;
    return rsq(l, mid, lq, rq, 2 * node + 1, n) + rsq(mid + 1, r, lq, rq, 2 * node + 2, n);
}

void update(int l, int r, int ind, int val, int node, int n) {
    if (l == r) {
        segtree[n][node] = val;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1, n);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2, n);
    }
    segtree[n][node] = segtree[n][2 * node + 1] + segtree[n][2 * node + 2];
}


void build(int l, int r, int node, int n) {
    if (l > r) {
        return;
    }
    if (l == r) {
        if (a[l] - 'a' == n) {
            segtree[n][node] = 1;
        } else {
            segtree[n][node] = 0;
        }
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1, n);
    build(mid + 1, r, 2 * node + 2, n);
    segtree[n][node] = segtree[n][2 * node + 1] + segtree[n][2 * node + 2];
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
    dfs(0, 1);
    cin >> vals;
    a = vals;
    for (int i = 0; i < n; i++) {
        a[tour[i]] = vals[i];
    }
    for (int j = 0; j < 26; j++) {
        build(0, n - 1, 0, j);
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int s; char x;
            cin >> s >> x;
            s--;
            update(0, n - 1, tour[s], 0, 0, a[tour[s]] - 'a');
            a[tour[s]] = x;
            update(0, n - 1, tour[s], 1, 0, x - 'a');
        }
        else {
            int s;
            cin >> s;
            s--;
            int k = 0;
            for (int j = 0; j < 26; j++) {
                k += rsq(0, n - 1, tour[s], tour[s] + sz[s] - 1, 0, j) % 2;
            }
            if (k <= 1) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}
