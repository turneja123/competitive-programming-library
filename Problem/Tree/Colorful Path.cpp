//https://marisaoj.com/problem/527
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int sz[N];
bool seen_c[N];
int parent_c[N];
vector<int> adj[N];

ll ans[N];
int ct[N];
int cols[N];
int sz_c[N];
int f = 0;
ll s_other = 0;

vector<int> restore;

void dfs_subtree(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_subtree(v, u);
            sz[u] += sz[v];
        }
    }
    return;
}

int dfs_centroid(int u, int p, int n) {
    for (int v : adj[u]) {
        if (v != p && !seen_c[v] && sz[v] > n / 2) {
            return dfs_centroid(v, u, n);
        }
    }
    return u;
}

void dfs_sz(int u, int p) {
    sz_c[u] = 1;
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_sz(v, u);
            sz_c[u] += sz_c[v];
        }
    }
}

void dfs_1(int u, int p, int c) {
    ct[a[u]]++;
    if (ct[a[u]] == 1) {
        s_other += sz_c[u];
        cols[a[u]] += sz_c[u];
        f++;
        restore.push_back(a[u]);
    }
    if (c != -1) {
        ans[c] += f + 1;
        ans[u] += f + 1;
    }
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_1(v, u, c);
        }
    }
    ct[a[u]]--;
    if (ct[a[u]] == 0) {
        f--;
    }
}

void dfs_2(int u, int p, ll s, int ct_other) {
    ct[a[u]]++;
    if (ct[a[u]] == 1) {
        f++;
        s += cols[a[u]];
    }
    ans[u] += (ll)ct_other * (f + 1) + s_other - s;

    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_2(v, u, s, ct_other);
        }
    }
    ct[a[u]]--;
    if (ct[a[u]] == 0) {
        f--;
        s -= cols[a[u]];
    }

}

void build(int u, int p) {
    dfs_subtree(u, u);
    int c = dfs_centroid(u, u, sz[u]);
    if (p == -1) {
        p = c;
    }
    parent_c[c] = p;
    seen_c[c] = true;

    ct[a[c]]++;

    int z = 0;
    for (int v : adj[c]) {
        if (!seen_c[v]) {
            dfs_sz(v, v);
            dfs_2(v, v, 0, z);
            dfs_1(v, v, c);
            z += sz_c[v];
        }
    }
    for (int x : restore) {
        cols[x] = 0;
    }
    restore.clear();
    f = 0;
    s_other = 0;
    z = 0;

    reverse(adj[c].begin(), adj[c].end());
    for (int v : adj[c]) {
        if (!seen_c[v]) {
            dfs_2(v, v, 0, z);
            dfs_1(v, v, -1);
            z += sz_c[v];
        }
    }
    for (int x : restore) {
        cols[x] = 0;
    }
    restore.clear();
    f = 0;
    s_other = 0;

    ct[a[c]]--;

    for (int v : adj[c]) {
        if (!seen_c[v]) {
            build(v, c);
        }
    }
    return;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    build(0, -1);
    for (int i = 0; i < n; i++) {
        cout << ans[i] + 1 << endl;
    }


    return 0;
}
