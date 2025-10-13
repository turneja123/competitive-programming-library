//https://codeforces.com/contest/2155/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int K = 19;

int tin[N];
int tout[N];
int up[K][N];
int cpy[N];
int depth[N];

int timer = 0;

vector<int> query[N];
vector<int> adj[N];
vector<int> colors[N];

void dfs(int u, int p) {
    tin[u] = timer++;
    up[0][u] = p;
    for (int k = 1; k < K; k++) {
        up[k][u] = up[k - 1][up[k - 1][u]];
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
    tout[u] = timer++;
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
    for (int k = K - 1; k >= 0; k--) {
        if (!is_ancestor(up[k][u], v)) {
            u = up[k][u];
        }
    }
    return up[0][u];
}

vector<tuple<int, int, int>> ask[N];
vector<int> stk[N];

void dfs_calc(int u, int p) {

    for (int c : colors[u]) {
        stk[c].push_back(u);
    }
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs_calc(v, u);
        }
    }
    for (auto [v, l, ind] : ask[u]) {
        int m = colors[v].size();
        for (int i = 0; i < m; i++) {
            int c = colors[v][i];
            int j = (int)stk[c].size() - 1 - (depth[u] - depth[l]);
            if (j >= 0 && stk[c][j] == l) {
                query[ind][i]++;
            }
        }
    }
    for (int c : colors[u]) {
        stk[c].pop_back();
    }
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k, s, q;
        cin >> n >> k >> s >> q;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int i = 0; i < s; i++) {
            int v, x;
            cin >> v >> x;
            v--, x--;
            colors[v].push_back(x);
        }
        dfs(0, 0);
        map<pair<int, int>, int> mp;
        vector<pair<int, int>> qe(q);
        for (int i = 0; i < q; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            if (colors[u].size() > colors[v].size() || (colors[u].size() == colors[v].size() && u > v)) {
                swap(u, v);
            }
            qe[i] = {u, v};
            if (mp.find({u, v}) != mp.end()) {
                cpy[i] = true;
                continue;
            }
            mp[{u, v}] = 0;
            int l = lca(u, v);
            if (colors[u].size()) {
                query[i].resize(colors[u].size(), 0);
            }
            ask[u].push_back({u, l, i});
            ask[v].push_back({u, l, i});
        }
        dfs_calc(0, 0);
        for (int i = 0; i < q; i++) {
            auto [u, v] = qe[i];
            if (!cpy[i]) {
                int ans = 0;
                for (int j = 0; j < query[i].size(); j++) {
                    if (query[i][j] == 2) {
                        ans++;
                    }
                }
                cout << ans << " ";
                mp[{u, v}] = ans;
            } else {
                cout << mp[{u, v}] << " ";
            }
            query[i].clear();
            cpy[i] = false;
        }
        cout << endl;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            colors[i].clear();
            ask[i].clear();
        }
        timer = 0;
    }

    return 0;
}
