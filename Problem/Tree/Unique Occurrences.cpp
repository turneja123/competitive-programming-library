//https://codeforces.com/contest/1681/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const int K = 21;

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
int sz[N];

bool seen[N];
int id[N];
int rev_id[N];

long long ans = 0;

long long dp[N];
long long subtree[N];

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(pair<uint64_t, uint64_t> x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return x.first * N + x.second + FIXED_RANDOM;
    }
};

gp_hash_table<pair<long long, long long>, int, custom_hash> good;

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

void dfs(int u, int p) {
    up[u] = p;
    pos[u] = euler;
    tour[euler++] = u;
    tin[u] = timer++;
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
            sz[u] += sz[v];
            tour[euler++] = u;
        }
    }
    tout[u] = timer++;
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

void calc_subtree(int u, int p) {
    subtree[u] = 0;
    int diff = sz[rev_id[u]];
    for (int v : aux[u]) {
        if (v != p) {
            calc_subtree(v, u);
            if (good.find(make_pair(min(rev_id[u], rev_id[v]), max(rev_id[u], rev_id[v]))) == good.end()) {
                subtree[u] += subtree[v];
            }
            diff -= sz[rev_id[v]];
        }
    }
    subtree[u] += diff;
    return;
}

void calc_dp(int u, int p, int n) {
    if (u == 0) {
        dp[u] = n - sz[rev_id[u]];
    }
    for (int v : aux[u]) {
        if (v != p) {
            if (good.find(make_pair(min(rev_id[u], rev_id[v]), max(rev_id[u], rev_id[v]))) != good.end()) {
                dp[v] = 0;
                ans += subtree[v] * (dp[u] + subtree[u]);
            } else {
                dp[v] = dp[u] + subtree[u] - subtree[v];
            }
            calc_dp(v, u, n);
        }
    }
    return;
}



int main() {
    IOS;
    int n;
    cin >> n;
    vector<tuple<int, int, int>> edges;
    for (int i = 1; i < n; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges.push_back(make_tuple(wt, u, v));
    }
    dfs(0, 0);
    build(2 * n - 1);
    sort(edges.begin(), edges.end());
    for (int i = 0; i < n - 1;) {
        vector<pair<int, int>> e;
        int cur = get<0>(edges[i]);
        while (i < n - 1 && get<0>(edges[i]) == cur) {
            int u = get<1>(edges[i]), v = get<2>(edges[i]);
            e.push_back(make_pair(u, v));
            good[make_pair(min(u, v), max(u, v))] = 1;
            i++;
        }
        vector<int> nodes;

        for (int j = 0; j < e.size(); j++) {
            auto [u, v] = e[j];
            if (!seen[u]) {
                nodes.push_back(u);
                seen[u] = true;
            }
            if (!seen[v]) {
                nodes.push_back(v);
                seen[v] = true;
            }
        }
        nodes = aux_tree(nodes);
        calc_subtree(0, 0);
        calc_dp(0, 0, n);
        for (int j = 0; j < nodes.size(); j++) {
            aux[j].clear();
            seen[nodes[j]] = false;
            subtree[j] = 0;
            dp[j] = 0;
            good.clear();
        }
    }
    cout << ans;
    return 0;
}
