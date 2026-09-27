//https://codeforces.com/contest/1045/problem/J
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int K = 17;

const ll M = 1e9 + 7;
const ll P = 26, INV_P = 576923081;
const ll Q = 53, INV_Q = 56603774;

ll pw_p[N], pw_q[N];
ll inv_p[N], inv_q[N];

vector<pair<int, char>> adj[N];
vector<tuple<int, int, int, string>> queries[101];

int sz[N];
int depth[N];
int up[K][N];
char up_c[N];

int id[N];
int pos[N];
int head[N];
int ans[N];


struct Path {
    int n;
    vector<int> path;
    vector<pair<ll, ll>> h_val_rising;
    vector<int> par;

    unordered_map<ll, vector<int>> mp;
    int j;

    Path() {

    }

    Path(vector<int> _path) {
        path = _path;
        n = path.size();
        h_val_rising.assign(n, make_pair(0, 0));
        par = path;
        j = 0;

    }

    void step() {
        mp.clear();

        for (int i = 0; i < path.size(); i++) {
            int u = path[i];
            int c = up_c[par[i]] - 'a' + 1;
            par[i] = up[0][par[i]];
            if (u == par[i]) {
                continue;
            }
            h_val_rising[i].first = (h_val_rising[i].first + pw_p[j] * c) % M;
            h_val_rising[i].second = (h_val_rising[i].second + pw_q[j] * c) % M;

            mp[h_val_rising[i].first + (h_val_rising[i].second << 32)].push_back(i);
        }

        j++;
    }

    int query(int l, int r, ll h) {
        auto it = mp.find(h);
        if (it == mp.end()) {
            return 0;
        }
        return upper_bound((it->second).begin(), (it->second).end(), r) - lower_bound((it->second).begin(), (it->second).end(), l);
    }
};

Path paths[N];

int query(int u, int v, ll h) {
    int ans = 0;
    while (1) {
        int j = id[u];
        int l = pos[u], r = (id[u] == id[v] ? pos[v] : paths[j].n - 1);
        ans += paths[j].query(l, r, h);
        if (id[u] == id[v]) {
            break;
        }
        u = up[0][paths[j].path.back()];
    }
    return ans;
}



void dfs_sz(int u, int p) {
    sz[u] = 1;
    up[0][u] = p;
    for (int i = 1; i < K; i++) {
        int v = up[i - 1][u];
        up[i][u] = up[i - 1][v];
    }

    for (auto [v, c] : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            up_c[v] = c;
            dfs_sz(v, u);
            sz[u] += sz[v];
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
            u = up[i][u];
        }
    }
    return u;
}

void dfs_hld(int u, int p) {
    for (auto [v, c] : adj[u]) {
        if (v != p) {
            if (2 * sz[v] >= sz[u]) {
                head[v] = 0;
            }
            dfs_hld(v, u);
        }
    }
}

int main() {
    IOS;
    pw_p[0] = 1, pw_q[0] = 1;
    inv_p[0] = 1, inv_q[0] = 1;
    for (int i = 1; i < N; i++) {
        pw_p[i] = pw_p[i - 1] * P % M;
        pw_q[i] = pw_q[i - 1] * Q % M;
        inv_p[i] = inv_p[i - 1] * INV_P % M;
        inv_q[i] = inv_q[i - 1] * INV_Q % M;
    }
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        head[i] = 1;
    }
    for (int i = 1; i < n; i++) {
        int u, v; char wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }
    dfs_sz(0, 0);
    dfs_hld(0, 0);

    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) {return depth[a] > depth[b];});
    vector<int> vis(n, 0);
    int m = 0;
    for (int i = 0; i < n; i++) {
        int u = ord[i];
        if (vis[u]) {
            continue;
        }
        vector<int> path;
        while (1) {
            vis[u] = 1;
            id[u] = m;
            pos[u] = path.size();
            path.push_back(u);
            if (head[u]) {
                break;
            }
            u = up[0][u];
        }
        paths[m] = Path(path);
        m++;
    }
    int step = 0;
    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        int u, v; string s;
        cin >> u >> v >> s;
        u--, v--;
        queries[s.size()].push_back({u, v, i, s});
    }
    for (int sz = 1; sz <= 100; sz++) {
        for (int j = 0; j < m; j++) {
            paths[j].step();
        }


        for (auto [u, v, ind, s] : queries[sz]) {
            ll p_rising = 0, q_rising = 0;
            ll p_falling = 0, q_falling = 0;
            for (int i = 0; i < s.size(); i++) {
                int c = s[i] - 'a' + 1;

                p_rising = (p_rising + pw_p[i] * c) % M;
                q_rising = (q_rising + pw_q[i] * c) % M;

                p_falling = (p_falling * P + c) % M;
                q_falling = (q_falling * Q + c) % M;
            }

            ll h_rising = p_rising + (q_rising << 32);
            ll h_falling = p_falling + (q_falling << 32);

            int l = lca(u, v);

            if (u != l) {
                int d = depth[u] - depth[l];
                if (d >= sz) {
                    int U = kth(u, d - sz);
                    ans[ind] += query(u, U, h_rising);
                }

            }
            if (l != v) {
                int d = depth[v] - depth[l];
                if (d >= sz) {
                    int V = kth(v, d - sz);
                    ans[ind] += query(v, V, h_falling);
                }
            }
            if (u != l && l != v) {
                vector<int> path_u, path_v;

                int du = depth[u] - depth[l];
                int dv = depth[v] - depth[l];
                if (du >= sz) {
                    u = kth(u, du - sz);
                }
                if (dv >= sz) {
                    v = kth(v, dv - sz);
                }
                while (u != l) {
                    path_u.push_back(u);
                    u = up[0][u];
                }
                while (v != l) {
                    path_v.push_back(v);
                    v = up[0][v];
                }
                reverse(path_v.begin(), path_v.end());
                vector<pair<int, int>> mix_path;
                for (int u : path_u) {
                    mix_path.push_back({u, 0});
                }
                for (int v : path_v) {
                    mix_path.push_back({v, 1});
                }
                ll p = 0, q = 0;
                for (int i = 0; i < mix_path.size(); i++) {
                    int c = up_c[mix_path[i].first] - 'a' + 1;
                    if (i - sz >= 0) {
                        int c_before = up_c[mix_path[i - sz].first] - 'a' + 1;
                        p = (p - c_before + M) * INV_P % M;
                        q = (q - c_before + M) * INV_Q % M;
                    }
                    p = (p + pw_p[min(i, sz - 1)] * c) % M;
                    q = (q + pw_q[min(i, sz - 1)] * c) % M;

                    ll h = p + (q << 32);
                    if (i >= sz - 1 && mix_path[i].second != mix_path[i - sz + 1].second && h == h_rising) {
                        ans[ind]++;
                    }
                }
            }
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
