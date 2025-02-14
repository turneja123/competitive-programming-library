//https://dmoj.ca/problem/oly18novp11
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e4 + 5;
const int K = 16;

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
vector<int> aux[N];
int tour[2 * N];

int depth[N];
int pos[N];
int euler = 0;
int timer = 0;
int table[K][2 * N];
int mn[K][2 * N];
int tin[N], tout[N];
int up[N];

bool orig[N];
bool seen[N];
int id[N];
int rev_id[N];

int tin_aux[N], tout_aux[N];
int up_aux[K][N];
int depth_aux[N];

int need[N];
int ans[N];
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

bool is_ancestor_aux(int u, int v) {
    return tin_aux[u] <= tin_aux[v] && tout_aux[v] <= tout_aux[u];
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
            u = up_aux[i][u];
        }
    }
    return u;
}

void dfs(int u, int p) {
    up[u] = p;
    pos[u] = euler;
    tour[euler++] = u;
    tin[u] = timer++;
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

void discover(int u, int p) {
    tin_aux[u] = timer++;
    up_aux[0][u] = p;
    for (int k = 1; k < K; k++) {
        up_aux[k][u] = up_aux[k - 1][up_aux[k - 1][u]];
    }

    for (int v : aux[u]) {
        if (v != p) {
            depth_aux[v] = depth_aux[u] + 1;
            discover(v, u);
        }
    }
    tout_aux[u] = timer++;
}

void dfs_calc1(int u, int p) {
    for (auto [ti, to] : weapons[u]) {
        bit.upd(ti, to, 1);
    }
    for (auto [v, j] : monsters[u]) {
        cur_ans[j] += bit.query(tin_aux[v]);
    }
    for (int v : aux[u]) {
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
        cur_ans[j] += bit.query(tin_aux[v]);
    }
    for (int v : aux[u]) {
        if (v != p) {
            dfs_calc2(v, u);
        }
    }
    for (auto [ti, to] : weapons[u]) {
        bit.upd(ti, to, 1);
    }
    return;
}

vector<int> aux_tree(vector<int> nodes) {
    sort(nodes.begin(), nodes.end(), [](int u, int v) {
        return tin[u] < tin[v];
    });
    int k = nodes.size();
    for (int i = 1; i < k; i++) {
        int l = lca(nodes[i - 1], nodes[i]);
        if (!seen[l]) {
            seen[l] = true;
            nodes.push_back(l);
        }
    }
    sort(nodes.begin(), nodes.end(), [](int u, int v) {
        return tin[u] < tin[v];
    });
    k = nodes.size();

    for (int i = 0; i < k; i++) {
        id[nodes[i]] = i;
        rev_id[i] = nodes[i];
    }

    vector<int> st;
    st.push_back(nodes[0]);
    for (int i = 1; i < k; i++) {
        int cur = nodes[i];
        while (!st.empty() && !is_ancestor(st.back(), cur)) {
            st.pop_back();
        }
        int u = st.back(), v = cur;
        aux[id[u]].push_back(id[v]);
        aux[id[v]].push_back(id[u]);
        st.push_back(cur);
    }

    return nodes;
}

void calc(int l, int r, vector<tuple<int, int, int>> &a) {
    if (a.empty()) {
        return;
    }
    int mid = (l + r) / 2;
    vector<int> nodes;
    for (int i = l; i <= mid; i++) {
        auto [u, v, wt] = events[i];
        if (!seen[u]) {
            seen[u] = true;
            orig[u] = true;
            nodes.push_back(u);
        }
        if (!seen[v]) {
            seen[v] = true;
            orig[v] = true;
            nodes.push_back(v);
        }
    }
    for (auto [u, v, j] : a) {
        if (!seen[u]) {
            seen[u] = true;
            orig[u] = true;
            nodes.push_back(u);
        }
        if (!seen[v]) {
            seen[v] = true;
            orig[v] = true;
            nodes.push_back(v);
        }
    }
    nodes = aux_tree(nodes);
    timer = 1;
    discover(0, 0);
    for (int i = l; i <= mid; i++) {
        auto [u, v, wt] = events[i];
        u = id[u], v = id[v];
        if (tin_aux[u] > tin_aux[v]) {
            swap(u, v);
        }
        if (is_ancestor_aux(u, v)) {
            continue;
        }
        weapons[u].push_back(make_pair(tin_aux[v], tout_aux[v]));
    }
    for (auto [u, v, j] : a) {
        u = id[u], v = id[v];
        if (tin_aux[u] > tin_aux[v]) {
            swap(u, v);
        }
        monsters[u].push_back(make_pair(v, j));
    }
    dfs_calc1(0, 0);
    for (int i = 0; i < nodes.size(); i++) {
        weapons[i].clear();
        monsters[i].clear();
    }

    for (int i = l; i <= mid; i++) {
        auto [u, v, wt] = events[i];
        u = id[u], v = id[v];
        if (tin_aux[u] > tin_aux[v]) {
            swap(u, v);
        }
        if (!is_ancestor_aux(u, v)) {
            continue;
        }
        bit.upd(tin_aux[v], tout_aux[v], 1);
        int d = depth_aux[v] - depth_aux[u];
        int anc = kth(v, d - 1);
        weapons[anc].push_back(make_pair(tin_aux[v], tout_aux[v]));
    }
    for (auto [u, v, j] : a) {
        u = id[u], v = id[v];
        if (tin_aux[u] > tin_aux[v]) {
            swap(u, v);
        }
        monsters[u].push_back(make_pair(v, j));
        monsters[v].push_back(make_pair(u, j));
    }
    dfs_calc2(0, 0);
    for (int i = l; i <= mid; i++) {
        auto [u, v, wt] = events[i];
        u = id[u], v = id[v];
        if (tin_aux[u] > tin_aux[v]) {
            swap(u, v);
        }
        if (!is_ancestor_aux(u, v)) {
            continue;
        }
        bit.upd(tin_aux[v], tout_aux[v], -1);
    }

    vector<tuple<int, int, int>> lf, rt;
    for (int i = 0; i < a.size(); i++) {
        int j = get<2>(a[i]);
        if (cur_ans[j] >= need[j]) {
            ans[j] = mid;
            lf.push_back(a[i]);
        } else {
            need[j] -= cur_ans[j];
            rt.push_back(a[i]);
        }
        cur_ans[j] = 0;
    }
    for (int i = 0; i < nodes.size(); i++) {
        aux[i].clear();
        weapons[i].clear();
        monsters[i].clear();
        seen[rev_id[i]] = false;
        orig[rev_id[i]] = false;
    }
    if (l <= mid - 1) {
        calc(l, mid - 1, lf);
    }
    if (mid + 1 <= r) {
        calc(mid + 1, r, rt);
    }
    return;
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
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        events.push_back(make_tuple(u, v, w));
    }
    sort(events.begin(), events.end(), [](auto u, auto v) {
        return get<2>(u) < get<2>(v);
    });
    vector<tuple<int, int, int>> queries;
    for (int i = 0; i < k; i++) {
        int u, v, k;
        cin >> u >> v >> k;
        u--, v--;
        queries.push_back(make_tuple(u, v, i));
        need[i] = k;
    }
    calc(0, m - 1, queries);
    for (int i = 0; i < k; i++) {
        int cost = get<2>(events[ans[i]]);
        cout << cost << endl;
    }
    return 0;
}
