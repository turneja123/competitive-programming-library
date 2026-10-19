//https://codeforces.com/contest/2236/problem/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int K = 17;

vector<int> adj[N];

int a[N];
int depth[N];
int depth_nonzero[N];

int up[K][N];
int up_nonzero[K][N];

int val[N];
ll pref[N];

void dfs_sz(int u, int p, int p_nonzero) {
    up[0][u] = p;
    for (int i = 1; i < K; i++) {
        int v = up[i - 1][u];
        up[i][u] = up[i - 1][v];
    }

    up_nonzero[0][u] = p_nonzero;
    for (int i = 1; i < K; i++) {
        int v = up_nonzero[i - 1][u];
        up_nonzero[i][u] = up_nonzero[i - 1][v];
    }

    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            depth_nonzero[v] = depth_nonzero[u] + (a[u] != 0);
            dfs_sz(v, u, (a[u] != 0 ? u : p_nonzero));
        }
    }
}

void dfs(int u, int p) {
    pref[u] += val[u];
    for (int v : adj[u]) {
        if (v != p) {
            pref[v] = pref[u];
            dfs(v, u);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] > depth[v]) {
        swap(u, v);
    }
    int d = depth[v] - depth[u];
    for (int i = K - 1; i >= 0; i--) {
        int c = d & (1 << i);
        if (c) {
            v = up[i][v];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = K - 1; i >= 0; i--) {
        if (up[i][u] != up[i][v]) {
            u = up[i][u];
            v = up[i][v];
        }
    }
    return up[0][u];
}

int kth(int u, int d) {
    for (int i = K - 1; i >= 0; i--) {
        int c = d & (1 << i);
        if (c) {
            u = up_nonzero[i][u];
        }
    }
    return u;
}



int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        int root = -1;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] != 0) {
                root = i;
            }
        }
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        if (root != -1) {
            dfs_sz(root, root, root);
            for (int i = 0; i < n; i++) {
                int u = i;
                int x = 0, y = 0;
                while (1) {
                    x += a[u], y |= a[u];
                    if (x != y) {
                        val[i] = depth[i] - depth[u];
                        break;
                    }
                    val[i] = depth[i] - depth[u] + 1;
                    if (u == root) {
                        break;
                    }
                    u = up_nonzero[0][u];
                }
            }
            dfs(root, root);
        } else {
            dfs_sz(0, 0, 0);
        }

        while (q--) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            if (depth[v] > depth[u]) {
                swap(u, v);
            }
            int anc = lca(u, v);
            if (root == -1) {
                int sz = depth[u] + depth[v] - 2 * depth[anc] + 1;
                ll ans = (ll)sz * (sz + 1) / 2;
                cout << ans << endl;
                continue;
            }

            vector<pair<int, int>> L, R;
            ll ans = 0;
            if (u != anc) {
                if (depth_nonzero[u] - depth_nonzero[anc] >= 25) {
                    int go = kth(u, depth_nonzero[u] - depth_nonzero[anc] - 25);
                    ans += pref[u] - pref[go];
                    u = go;
                }
                while (depth[u] > depth[anc]) {
                    L.push_back({u, 0});
                    u = up_nonzero[0][u];
                }
                L.push_back({anc, 0});
            }
            if (v != anc) {
                if (depth_nonzero[v] - depth_nonzero[anc] >= 25) {
                    int go = kth(v, depth_nonzero[v] - depth_nonzero[anc] - 25);
                    ans += pref[v] - pref[go];
                    v = go;
                }
                while (depth[v] > depth[anc]) {
                    R.push_back({v, 1});
                    v = up_nonzero[0][v];
                }
                reverse(R.begin(), R.end());
                for (auto x : R) {
                    L.push_back(x);
                }
            }
            int r = 0;
            int x = 0, y = 0;

            while (r != L.size()) {
                int x_nx = x + a[L[r].first], y_nx = y ^ a[L[r].first];
                if (x_nx != y_nx) {
                    break;
                }
                x = x_nx, y = y_nx;
                r++;
            }
            auto dist = [&](pair<int, int> a, pair<int, int> b) -> int {
                int u = a.first, v = b.first;
                if (a.second != b.second) {
                    return depth[u] + depth[v] - 2 * depth[anc];
                }
                return abs(depth[u] - depth[v]);
            };
            for (int i = 0; i < L.size(); i++) {
                if (i > 0) {
                    x -= a[L[i - 1].first];
                    y ^= a[L[i - 1].first];
                    while (r != L.size()) {
                        int x_nx = x + a[L[r].first];
                        int y_nx = y ^ a[L[r].first];
                        if (x_nx != y_nx) {
                            break;
                        }
                        x = x_nx;
                        y = y_nx;
                        r++;
                    }
                }
                int X = (i == 0 ? 1 : dist(L[i - 1], L[i]));
                int D = (r == L.size() ? dist(L[i], L.back()) : dist(L[i], L[r]) - 1);
                int Y = D + X;
                ans += (ll)X * Y;
                ans -= (ll)X * (X - 1) / 2;
            }
            cout << ans << endl;
        }
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            val[i] = 0;
            pref[i] = 0;
            depth[i] = 0;
            depth_nonzero[i] = 0;
        }
    }


    return 0;
}
