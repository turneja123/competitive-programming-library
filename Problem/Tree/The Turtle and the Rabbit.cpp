//https://dmoj.ca/problem/aaaa1p6
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 18;

vector<int> adj[N];
int tin[N];
int tout[N];
int up[K][N];
int timer = 0;

int subtree[N];
int aux[N];
int child[N];
int dp[N];
int depth[N];


void dfs(int u, int p) {
    tin[u] = timer++;
    up[0][u] = p;
    for (int k = 1; k < K; k++) {
        up[k][u] = up[k - 1][up[k - 1][u]];
    }
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
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
    tout[u] = timer++;
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

int kth(int u, int v, int l, int k) {
    int w;
    int d1 = depth[u] - depth[l];
    if (k <= d1) {
        w = u;
        for (int i = K - 1; i >= 0; i--) {
            int c = k & (1 << i);
            if (c) {
                w = up[i][w];
            }
        }
    } else {
        int d2 = depth[v] - depth[l];
        k = d1 + d2 - k, w = v;
        for (int i = K - 1; i >= 0; i--) {
            int c = k & (1 << i);
            if (c) {
                w = up[i][w];
            }
        }
    }
    return w;

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
    dfs_dp(0, 0);
    for (int i = 0; i < q; i++) {
        int t, u, v;
        cin >> t >> u >> v;
        u--, v--;
        if (t == 1) {
            int l = lca(u, v);
            int d = depth[u] + depth[v] - 2 * depth[l];
            int k = d / 3;
            int w = kth(u, v, l, k);

            if (is_ancestor(w, v)) {
                w = kth(u, v, l, k + 1);
                int ans = d / 3 + 1 + subtree[w];
                cout << 2 * ans << endl;
            } else {
                int ans = d / 3 + dp[w];
                cout << 2 * ans << endl;
            }

        } else {
            int l = lca(u, v);
            int d = depth[u] + depth[v] - 2 * depth[l];
            int lf = 0, rt = d / 3, ans = 0;
            while (lf <= rt) {
                int mid = (lf + rt) / 2;
                int w = kth(v, u, l, mid);

                int costl, costr;
                if (is_ancestor(w, v) && w != l) {
                    costl = d - mid + d - 3 * mid;
                    costr = d - mid + subtree[w];
                } else {
                    w = kth(v, u, l, mid + 1);
                    costl = d - mid + d - 3 * mid;
                    costr = d - mid + dp[w] - 1;
                }
                ans = max(ans, min(costl, costr));
                if (costl >= costr) {
                    lf = mid + 1;
                } else {
                    rt = mid - 1;
                }
            }
            cout << ans << endl;
        }



    }
    return 0;
}
