//https://dmoj.ca/problem/joi20scd4p1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int sz[N];
bool seen_c[N];
int parent_c[N];
int color[N];
vector<int> adj[N];

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

vector<int> colors[N];
vector<int> q;
bool seen[N];
bool seen_subtree[N];
bool seen_color[N];
int parent[N];

vector<int> restore;

int ct, ans = N;

void dfs_depth(int u, int p, int cent) {
    parent[u] = p;
    if (color[u] == color[cent]) {
        q.push_back(u);
        seen[u] = true;
    }
    restore.push_back(u);
    seen_subtree[u] = true;

    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_depth(v, u, cent);
        }
    }

    return;
}

void build(int u, int p) {
    dfs_subtree(u, u);
    int c = dfs_centroid(u, u, sz[u]);
    if (p == -1) {
        p = c;
    }
    parent_c[c] = p;
    seen_c[c] = true;
    parent[c] = c;

    int can = 1;
    ct = 0;
    restore.push_back(c);
    q.push_back(c);
    seen[c] = true;
    seen_subtree[c] = true;
    seen_color[color[c]] = true;

    for (int v : adj[c]) {
        if (!seen_c[v]) {
            dfs_depth(v, c, c);
        }
    }

    if (q.size() != colors[color[c]].size()) {
        can = 0;
    } else {
        while (q.size() && can) {
            int u = q.back();
            u = parent[u];
            q.pop_back();
            while (!seen[u] && can) {
                seen[u] = true;
                q.push_back(u);
                if (!seen_color[color[u]]) {
                    ct++;
                    seen_color[color[u]] = true;
                    for (int v : colors[color[u]]) {
                        if (!seen_subtree[v]) {
                            can = 0;
                            break;
                        }
                        if (!seen[v]) {
                            seen[v] = true;
                            q.push_back(v);
                        }
                    }
                }
                u = parent[u];
            }
        }
    }
    if (can) {
        ans = min(ans, ct);
    }
    q.clear();
    for (int u : restore) {
        seen[u] = false;
        seen_color[color[u]] = false;
        seen_subtree[u] = false;
    }
    restore.clear();

    for (int v : adj[c]) {
        if (!seen_c[v]) {
            build(v, c);
        }
    }
    return;
}

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        cin >> color[i];
        colors[color[i]].push_back(i);
    }
    build(0, -1);
    cout << ans;


    return 0;
}
