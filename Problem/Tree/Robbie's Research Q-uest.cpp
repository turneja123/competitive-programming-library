//https://codesprintla26.kattis.com/contests/codesprintla26open/problems/robbiesresearchquest
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int K = 19;

vector<int> adj[N];
multiset<int> st[N];

int up[K][N];
int mx[K][N];

int depth[N];
int low[N];

void dfs(int u, int p) {
    low[u] = depth[u];
    up[0][u] = p;
    for (int k = 1; k < K; k++) {
        int v = up[k - 1][u];
        up[k][u] = up[k - 1][v];
    }
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
            low[u] = max(low[u], low[v]);
            st[u].insert(low[v] - depth[u]);
        }
    }

    return;
}

void dfs_calc(int u, int p) {
    if (p == u) {
        mx[0][u] = 0;
    } else {
        st[p].erase(st[p].find(low[u] - depth[p]));
        if (st[p].size()) {
            auto it = st[p].rbegin();
            mx[0][u] = *it;
            it++;
            if (it != st[p].rend()) mx[0][u] += *it;
        } else {
            mx[0][u] = 0;
        }
        st[p].insert(low[u] - depth[p]);
    }
    for (int k = 1; k < K; k++) {
        int v = up[k - 1][u];
        mx[k][u] = max(mx[k - 1][u], mx[k - 1][v]);
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs_calc(v, u);
        }
    }
    return;
}

int lca(int u, int v) {
    if (depth[v] > depth[u]) {
        swap(u, v);
    }
    int x = depth[u] - depth[v];
    for (int k = K - 1; k >= 0; k--) {
        int c = x & (1 << k);
        if (c) {
            u = up[k][u];
        }
    }
    if (u == v) {
        return u;
    }
    for (int k = K - 1; k >= 0; k--) {
        if (up[k][u] != up[k][v]) {
            u = up[k][u], v = up[k][v];
        }
    }
    return up[0][u];
}

int subtree[N];
int aux[N];
int child[N];
int dp[N];

void dfs_subtree(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs_subtree(v, u);
            if (subtree[v] + 1 > subtree[u]) {
                subtree[u] = subtree[v] + 1;
                child[u] = v;
            }
        }
    }
    for (int v : adj[u]) {
        if (v != p && v != child[u]) {
            aux[u] = max(aux[u], subtree[v] + 1);
        }
    }
}

void dfs_dp(int u, int p) {
    for (int v : adj[u]) {
        if (v != p && v != child[u]) {
            dp[v] = max(dp[u] + 1, subtree[u] + 1);
        } else if (v != p && v == child[u]) {
            dp[v] = max(dp[u] + 1, aux[u] + 1);
        }
        if (v != p) {
            dfs_dp(v, u);
        }
    }
}

int main() {
    IOS;

    int n, q;
    cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 0);
    dfs_calc(0, 0);
    dfs_subtree(0, 0);
    dfs_dp(0, 0);

    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (depth[v] > depth[u]) {
            swap(u, v);
        }
        int l = lca(u, v);
        if (v == l && depth[u] - depth[v] == 1) {
            cout << -1 << endl;
            continue;
        }

        int best = 0;
        if (st[u].size()) {
            int cur = 0;
            auto it = st[u].rbegin();
            cur += *it;
            it++;
            if (it != st[u].rend()) cur += *it;
            best = max(best, cur);
        }
        if (l != v && st[v].size()) {
            int cur = 0;
            auto it = st[v].rbegin();
            cur += *it;
            it++;
            if (it != st[v].rend()) cur += *it;
            best = max(best, cur);
        }

        int x = u, d = depth[x] - depth[l] - 1;
        for (int i = K - 1; i >= 0; i--) {
            int c = (1 << i) & d;
            if (c) {
                best = max(best, mx[i][x]);
                x = up[i][x];
            }
        }
        int U = x, V = -1;
        st[l].erase(st[l].find(low[U] - depth[l]));

        if (v != l) {
            int x = v, d = depth[x] - depth[l] - 1;
            for (int i = K - 1; i >= 0; i--) {
                int c = (1 << i) & d;
                if (c) {
                    best = max(best, mx[i][x]);
                    x = up[i][x];
                }
            }
            V = x;
            st[l].erase(st[l].find(low[V] - depth[l]));
        }

        if (dp[l]) {
            st[l].insert(dp[l]);
        }

        if (st[l].size()) {
            int cur = 0;
            auto it = st[l].rbegin();
            cur += *it;
            it++;
            if (it != st[l].rend()) cur += *it;
            best = max(best, cur);
        }

        st[l].insert(low[U] - depth[l]);
        if (V != -1) {
            st[l].insert(low[V] - depth[l]);
        }
        if (dp[l]) {
            st[l].erase(st[l].find(dp[l]));
        }
        if (best == 0) {
            cout << -1 << endl;
        } else {
            cout << depth[u] + depth[v] - 2 * depth[l] + 1 + best << endl;
        }
    }


    return 0;
}
