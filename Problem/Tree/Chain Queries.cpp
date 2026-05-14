//https://codeforces.com/contest/1975/problem/E
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
int depth[N];
int ct[N];
int timer = 0;

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

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 1; i < n; i++) {
            int u,v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(0, 0);
        set<int> leaf;
        set<pair<int, int>> st;

        auto add = [&](int u) -> void {
            a[u] = 1;
            if (u != 0) {
                ct[up[0][u]]++;
                if (a[up[0][u]] && ct[up[0][u]] == 1) {
                    leaf.erase(up[0][u]);
                }
            }
            if (ct[u] == 0) {
                leaf.insert(u);
            }
            st.insert({depth[u], u});
        };

        auto rem = [&](int u) -> void {
            a[u] = 0;
            if (u != 0) {
                ct[up[0][u]]--;
                if (a[up[0][u]] && ct[up[0][u]] == 0) {
                    leaf.insert(up[0][u]);
                }
            }
            if (ct[u] == 0) {
                leaf.erase(u);
            }
            st.erase({depth[u], u});
        };

        for (int i = 0; i < n; i++) {
            if (a[i]) {
                add(i);
            }
        }

        for (int i = 0; i < q; i++) {
            int u;
            cin >> u;
            u--;
            if (!a[u]) {
                add(u);
            } else {
                rem(u);
            }
            if (st.empty() || leaf.size() > 2) {
                cout << "No" << endl;
                continue;
            }
            if (st.size() == 1) {
                cout << "Yes" << endl;
                continue;
            }
            auto it = leaf.begin();
            int l = st.begin()->second; u = *it;
            if (leaf.size() == 1) {
                if (is_ancestor(l, u) && st.size() == depth[u] - depth[l] + 1) {
                    cout << "Yes" << endl;
                } else {
                    cout << "No" << endl;
                }
                continue;
            }
            it++;
            int v = *it;
            if (lca(u, v) == l && st.size() == depth[u] + depth[v] - 2 * depth[l] + 1) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
        timer = 0;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            ct[i] = 0;
        }
    }
    return 0;
}
