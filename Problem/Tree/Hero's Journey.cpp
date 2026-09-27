//bbc16
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const ll INF = 1e18;

ll ans[N];
vector<int> adj[N];
vector<pair<ll, int>> queries[N];

set<pair<ll, ll>> st[N];
ll off_key[N];
ll off_val[N];

ll s[N];
ll m[N];
int parent[N];

int dsu_find(int u) {
    if (u == parent[u]) {
        return u;
    }
    return parent[u] = dsu_find(parent[u]);
}

void sorted_set_insert(ll key, ll val, set<pair<ll, ll>> &st, ll off_key, ll off_val) {
    auto it = st.lower_bound(make_pair(key - off_key, -INF));
    if (it != st.end() && it->first + off_key == key && it->second + off_val >= val) {
        return;
    }

    if (it != st.begin()) {
        it--;
        if (it->second + off_val >= val) {
            return;
        }
        it++;
    }
    while (it != st.end() && it->second + off_val <= val) {
        it = st.erase(it);
    }
    st.insert(make_pair(key - off_key, val - off_val));
}

void dsu_unite(int u, int v) {
    u = dsu_find(u), v = dsu_find(v);
    if (st[u].size() > st[v].size()) {
        swap(u, v);
    }
    for (auto [key, val] : st[u]) {
        key += off_key[u];
        val += off_val[u];
        sorted_set_insert(key, val, st[v], off_key[v], off_val[v]);
    }
    st[u].clear();
    parent[u] = v;
}


void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            dsu_unite(u, v);
        }
    }
    int a = dsu_find(u);
    off_key[a] += m[u] - s[u];
    off_val[a] += s[u] - m[u];
    ll mx = s[u] - m[u];

    while (st[a].size() && st[a].begin()->first + off_key[a] < m[u]) {
        mx = max(mx, st[a].begin()->second + off_val[a]);
        st[a].erase(st[a].begin());
    }
    sorted_set_insert(m[u], mx, st[a], off_key[a], off_val[a]);


    for (auto [x, i] : queries[u]) {
        ans[i] = x;
        auto it = st[a].lower_bound(make_pair(x - off_key[a], INF));
        if (it != st[a].begin()) {
            it--;
            ans[i] = max(ans[i], x + it->second + off_val[a]);
        }
    }

}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        parent[i] = i;
    }
    for (int i = 0; i < n; i++) {
        cin >> m[i];
    }
    for (int i = 0; i < q; i++) {
        int u; ll x;
        cin >> u >> x;
        u--;
        queries[u].push_back({x, i});
    }
    dfs(0, 0);
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
