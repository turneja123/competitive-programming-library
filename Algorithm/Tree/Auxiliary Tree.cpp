//https://codeforces.com/contest/613/problem/D
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

bool orig[N];
bool seen[N];
int id[N];
int rev_id[N];

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

pair<int, int> calc(int u, int p) {
    int ans = 0, ct = 0, fl = 0;
    for (int v : aux[u]) {
        if (v != p) {
            pair<int, int> cur = calc(v, u);
            ans += cur.first;
            if (cur.second) {
                ct++;
            }
            if (orig[rev_id[u]] && cur.second) {
                ans++;
            }
        }
    }
    if (!orig[rev_id[u]] && ct > 1) {
        return make_pair(ans + 1, 0);
    }
    if (!orig[rev_id[u]] && ct == 0) {
        return make_pair(ans, 0);
    }
    return make_pair(ans, 1);
}

int main() {
    IOS;
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
    build(2 * n - 1);
    cin >> q;
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        vector<int> nodes;
        for (int j = 0; j < k; j++) {
            int u;
            cin >> u;
            u--;
            nodes.push_back(u);
            seen[u] = true;
            orig[u] = true;
        }
        bool can = true;
        for (int x : nodes) {
            if (x != 0 && orig[up[x]]) {
                can = false;
            }
        }
        if (can) {
            nodes = aux_tree(nodes);
            cout << calc(0, 0).first << endl;
        } else {
            cout << -1 << endl;
        }
        for (int j = 0; j < nodes.size(); j++) {
            aux[j].clear();
            seen[nodes[j]] = false;
            orig[nodes[j]] = false;
        }
    }
    return 0;
}
