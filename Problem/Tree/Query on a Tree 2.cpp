//solution for https://www.spoj.com/problems/QTREE2/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int timer, lg;

vector<vector<pair<int, ll>>> adj;
vector<int> tin, tout, depth;
vector<ll> dist;
vector<vector<int>> up;

void dfs(int v, int p) {
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= lg; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (pair<int, ll> u : adj[v]) {
        if (u.first != p) {
            dist[u.first] = dist[v] + u.second;
            depth[u.first] = depth[v] + 1;
            dfs(u.first, v);
        }
    }
    tout[v] = ++timer;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) {
        return u;
    }
    if (is_ancestor(v, u)) {
        return v;
    }
    for (int i = lg; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v)) {
            u = up[u][i];
        }
    }
    return up[u][0];
}

int kth(int u, int v, int k) {
    int a = lca(u, v);
    if (depth[u] - depth[a] + 1 >= k) {
        k--;
        while (k > 0) {
            int l = log2(k);
            u = up[u][l];
            k ^= 1 << l;
        }
        return u;
    }
    k -= depth[u] - depth[a] + 1;
    k = depth[v] - depth[a] - k;
    while (k > 0) {
        int l = log2(k);
        v = up[v][l];
        k ^= 1 << l;
    }
    return v;


}

ll dist_q(int u, int v) {
    int a = lca(u, v);
    return dist[u] + dist[v] - 2 * dist[a];
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        tin.resize(n);
        tout.resize(n);
        depth.resize(n);
        dist.resize(n);
        timer = 0;
        lg = ceil(log2(n));
        up.assign(n, vector<int>(lg + 1));
        adj.assign(n, vector<pair<int, ll>>(0));
        for (int i = 0; i < n - 1; i++) {
            int a, b; ll wt;
            cin >> a >> b >> wt;
            a--, b--;
            adj[a].push_back({b, wt});
            adj[b].push_back({a, wt});
        }
        dfs(0, 0);
        while (1) {
            string q;
            cin >> q;
            if (q == "DONE") {
                break;
            }
            if (q == "DIST") {
                int u, v;
                cin >> u >> v;
                u--, v--;
                cout << dist_q(u, v) << endl;
            } else {
                int u, v, k;
                cin >> u >> v >> k;
                u--, v--;
                cout << kth(u, v, k) + 1 << endl;
            }
        }
        tin.clear();
        tout.clear();
        depth.clear();
        dist.clear();
        up.clear();
        adj.clear();
    }
    return 0;
}
