//https://codesprintla25.kattis.com/contests/codesprintla25open/problems/chemtechcontagion
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int K = 20;

struct BIT {
    int n;
    vector<int> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    void upd(int i, int val) {
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
        }
    }
    void upd(int l, int r, int val) {
        upd(l, val);
        upd(r + 1, -val);
    }
    int query(int i) {
        int ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
};

BIT bit(2 * N);

vector<int> adj[N];
int tour[2 * N];

int depth[N];
int pos[N];
int euler = 0;
int timer = 0;
int table[K][2 * N];
int mn[K][2 * N];
int tin[N], tout[N];
int up[K][N];

bool orig[N];
bool seen[N];

int cur_ans[N];
vector<tuple<int, int, int>> events;
vector<pair<int, int>> weapons[N];
vector<pair<int, int>> monsters[N];

void build(int n) {
    for (int i = 1; i <= n; i++) {
        int u = tour[i - 1];
        table[0][i] = depth[u];
        mn[0][i] = u;
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            if (table[k - 1][i] < table[k - 1][i + (1 << (k - 1))]) {
                table[k][i] = table[k - 1][i];
                mn[k][i] = mn[k - 1][i];
            } else {
                table[k][i] = table[k - 1][i + (1 << (k - 1))];
                mn[k][i] = mn[k - 1][i + (1 << (k - 1))];
            }
        }
    }
    return;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int query(int l, int r) {
    l++, r++;
    int k = 31 - __builtin_clz(r - l + 1);
    if (table[k][l] < table[k][r - (1 << k) + 1]) {
        return mn[k][l];
    }
    return mn[k][r - (1 << k) + 1];
}

int lca(int a, int b) {
    int l = pos[a];
    int r = pos[b];
    if (l > r) {
        swap(l, r);
    }
    return query(l, r);
}

int kth(int u, int k) {
    for (int i = K - 1; i >= 0; i--) {
        int c = k & (1 << i);
        if (c) {
            u = up[i][u];
        }
    }
    return u;
}

void dfs(int u, int p) {
    pos[u] = euler;
    tour[euler++] = u;
    tin[u] = timer++;
    up[0][u] = p;
    for (int k = 1; k < K; k++) {
        up[k][u] = up[k - 1][up[k - 1][u]];
    }

    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
            tour[euler++] = u;
        }
    }
    tout[u] = timer++;
    return;
}


void dfs_calc1(int u, int p) {
    for (auto [ti, to] : weapons[u]) {
        bit.upd(ti, to, 1);
    }
    for (auto [v, j] : monsters[u]) {
        cur_ans[j] += bit.query(tin[v]);
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs_calc1(v, u);
        }
    }
    for (auto [ti, to] : weapons[u]) {
        bit.upd(ti, to, -1);
    }
    return;
}

void dfs_calc2(int u, int p) {
    for (auto [ti, to] : weapons[u]) {
        bit.upd(ti, to, -1);
    }
    for (auto [v, j] : monsters[u]) {
        cur_ans[j] += bit.query(tin[v]);
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs_calc2(v, u);
        }
    }
    for (auto [ti, to] : weapons[u]) {
        bit.upd(ti, to, 1);
    }
    return;
}

void calc(int m, int n, vector<tuple<int, int, int>> &a) {
    if (a.empty()) {
        return;
    }
    timer = 1;
    for (int i = 0; i < m; i++) {
        auto [u, v, wt] = events[i];
        if (tin[u] > tin[v]) {
            swap(u, v);
        }
        if (is_ancestor(u, v)) {
            continue;
        }
        weapons[u].push_back(make_pair(tin[v], tout[v]));
    }
    for (auto [u, v, j] : a) {
        if (tin[u] > tin[v]) {
            swap(u, v);
        }
        monsters[u].push_back(make_pair(v, j));
    }
    dfs_calc1(0, 0);
    for (int i = 0; i < n; i++) {
        weapons[i].clear();
        monsters[i].clear();
    }

    for (int i = 0; i < m; i++) {
        auto [u, v, wt] = events[i];
        if (tin[u] > tin[v]) {
            swap(u, v);
        }
        if (!is_ancestor(u, v)) {
            continue;
        }
        bit.upd(tin[v], tout[v], 1);
        int d = depth[v] - depth[u];
        int anc = kth(v, d - 1);
        weapons[anc].push_back(make_pair(tin[v], tout[v]));
    }
    for (auto [u, v, j] : a) {
        if (tin[u] > tin[v]) {
            swap(u, v);
        }
        monsters[u].push_back(make_pair(v, j));
        monsters[v].push_back(make_pair(u, j));
    }
    dfs_calc2(0, 0);
    return;
}

int deg[N];
int pref[N];

void dfs_pref(int u, int p) {
    pref[u] += deg[u];
    for (int v : adj[u]) {
        if (v != p) {
            pref[v] += pref[u];
            dfs_pref(v, u);
        }
    }
}

int main() {
    IOS;
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 0);
    build(2 * n - 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        events.push_back(make_tuple(u, v, 1));
        deg[u]++;
        deg[v]++;
    }
    vector<tuple<int, int, int>> queries;
    for (int i = 0; i < k; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        queries.push_back(make_tuple(u, v, i));
    }
    calc(m, n, queries);
    dfs_pref(0, 0);
    for (int i = 0; i < k; i++) {
        auto [u, v, wt] = queries[i];
        int l = lca(u, v);
        int ans = pref[u] + pref[v] - 2 * pref[l] + deg[l];
        cout << ans - 2 * cur_ans[i] << endl;
    }
    return 0;
}
