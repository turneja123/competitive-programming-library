//https://dmoj.ca/problem/ceoi19p5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const ll INF = 1e18;


vector<int> adj[N];
int d[N];
int w[N];
int parent[N];
set<pair<int, ll>> st[N];

int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

void dsu_merge(int a, int b) {
    if (st[a].size() > st[b].size()) {
        swap(a, b);
    }
    parent[a] = b;
    for (auto [i, add] : st[a]) {
        if (st[b].empty()) {
            st[b].insert({i, add});
            continue;
        }
        auto f = st[b].lower_bound({i, -1});
        if (f == st[b].end() || f->first != i) {
            st[b].insert({i, add});
            continue;
        }
        add += f->second;
        st[b].erase(f);
        st[b].insert({i, add});
    }
    return;
}

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            int a = dsu_find(u), b = dsu_find(v);
            dsu_merge(a, b);
        }
    }
    if (d[u] != -1) {
        ll add = w[u];
        int a = dsu_find(u);
        if (st[a].empty()) {
            st[a].insert({d[u], add});
            return;
        }
        auto f = st[a].lower_bound({d[u], -1});
        if (f == st[a].end() || f->first != d[u]) {
            st[a].insert({d[u], add});
        } else {
            ll inc = add + f->second;
            st[a].erase(f);
            st[a].insert({d[u], inc});
        }
        auto it = st[a].upper_bound({d[u], INF});
        while (it != st[a].end()) {
            if (add <= it->second) {
                int cur = it->first; ll nx = it->second - add;
                st[a].erase(it);
                if (nx != 0) {
                    st[a].insert({cur, nx});
                }
                break;

            } else {
                add -= it->second;
                it = st[a].erase(it);
            }
        }
    }

}

int main() {
    IOS;
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        d[i] = -1;
        w[i] = -1;
        parent[i] = i;
        if (i == 0) {
            continue;
        }
        int p;
        cin >> p;
        p--;
        adj[p].push_back(i);
        adj[i].push_back(p);
    }
    for (int i = 0; i < m; i++) {
        int v, D, W;
        cin >> v >> D >> W;
        v--;
        d[v] = D;
        w[v] = W;
    }
    dfs(0, 0);
    ll ans = 0;
    int a = dsu_find(0);
    for (auto [_, add] : st[a]) {
        ans += add;
    }
    cout << ans;


    return 0;
}
