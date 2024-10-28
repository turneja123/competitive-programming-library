//https://codeforces.com/contest/2033/problem/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int MAX = 1e7 + 5;
const int K = 19;

vector<int> adj[N];
multiset<int> st[N];

int up[K][N];
int mx[K][N];

int depth[N];
int subtree[N];

void dfs(int u, int p) {
    subtree[u] = depth[u];
    up[0][u] = p;
    for (int k = 1; k < K; k++) {
        int v = up[k - 1][u];
        up[k][u] = up[k - 1][v];
    }
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
            st[u].insert(subtree[v]);
        }
    }
    if (st[u].size()) {
        subtree[u] = max(subtree[u], *st[u].rbegin());
    }
    return;
}

void dfs_calc(int u, int p) {
    if (p == u) {
        mx[0][u] = -MAX;
    } else {
        st[p].erase(st[p].find(subtree[u]));
        if (st[p].size()) {
            mx[0][u] = *st[p].rbegin() - 2 * depth[p];
        } else {
            mx[0][u] = -MAX;
        }
        st[p].insert(subtree[u]);
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

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n;
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(0, 0);
        dfs_calc(0, 0);

        cin >> q;
        for (int i = 0; i < q; i++) {
            int u, d;
            cin >> u >> d;
            u--;
            int ans = subtree[u] - depth[u];
            int anc = u;
            for (int k = K - 1; k >= 0; k--) {
                int c = d & (1 << k);
                if (c) {
                    ans = max(ans, mx[k][anc] + depth[u]);
                    anc = up[k][anc];
                }
            }
            ans = max(ans, depth[u] - depth[anc]);
            cout << ans << " ";
        }
        cout << endl;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            st[i].clear();
            depth[i] = 0;
            for (int k = K - 1; k >= 0; k--) {
                up[k][i] = 0;
                mx[k][i] = 0;
            }
        }
    }
    return 0;
}

