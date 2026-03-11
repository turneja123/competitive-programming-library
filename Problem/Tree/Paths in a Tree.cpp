//https://www.spoj.com/problems/CQM1TREE/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<int> adj[N];
int need[N];
int low[N];
int who[N];
int depth[N];
int sz[N];

int ok = 0;


void dfs(int u, int p, int root) {
    sz[u] = 1;
    int child = 0;
    if (need[u]) {
        low[u] = depth[u];
        who[u] = u;
    } else {
        low[u] = -1;
    }
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u, root);
            sz[u] += sz[v];
            if (low[u] < low[v]) {
                low[u] = low[v];
                who[u] = who[v];
            }

            if (need[v]) {
                need[u] = 1;
                child++;
            }
        }
    }
    if (child > 1 && u != root) {
        ok = 0;
    }
    if (child > 2) {
        ok = 0;
    }
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        assert(k);
        vector<pair<int, int>> edges;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
            edges.push_back({u, v});
        }
        int root = 0;
        for (int i = 0; i < k; i++) {
            int j;
            cin >> j;
            auto [u, v] = edges[j];
            need[u] = 1, need[v] = 1;
            root = u;
        }
        ok = 1;
        dfs(root, root, root);
        if (!ok) {
            cout << 0 << endl;
        } else {
            vector<int> child;
            for (int v : adj[root]) {
                if (need[v]) {
                    child.push_back(v);
                }
            }
            ll ans = 0;
            if (child.size() == 1) {
                int s = 0;
                for (int v : adj[root]) {
                    if (v != child[0]) {
                        s += sz[v];
                    }
                }
                ans = (ll)(s + 1) * sz[who[child[0]]];
            } else {
                ans = (ll)sz[who[child[0]]] * sz[who[child[1]]];
            }
            cout << ans << endl;
        }
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            need[i] = 0;
        }
    }

    return 0;
}
