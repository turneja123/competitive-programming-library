//https://arena.petlja.org/competition/20202021kvalifikacije1-vezba#tab_133364
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int parent[N];
vector<pair<int, int>> adj[N];
map<vector<int>, long long> st[N];
vector<vector<int>> colors;
long long ans = 0;

int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

void dsu_merge(int a, int b, vector<int> &lca) {
    if (st[a].size() > st[b].size()) {
        swap(a, b);
    }
    parent[a] = b;
    for (auto it = st[a].begin(); it != st[a].end(); ++it) {
        vector<int> v = it->first;
        v[0] -= lca[0], v[1] -= lca[1], v[2] -= lca[2];
        int mn = min({v[0], v[1], v[2]});
        v[0] -= mn, v[1] -= mn, v[2] -= mn;
        int mx = max({v[0], v[1], v[2]});
        vector<int> complement(3, 0);
        complement[0] = mx - v[0] + lca[0];
        complement[1] = mx - v[1] + lca[1];
        complement[2] = mx - v[2] + lca[2];
        mn = min({complement[0], complement[1], complement[2]});
        complement[0] -= mn, complement[1] -= mn, complement[2] -= mn;
        auto f = st[b].find(complement);
        if (f != st[b].end()) {
            ans += it->second * f->second;
        }
    }
    for (auto it = st[a].begin(); it != st[a].end(); ++it) {
        st[b][it->first] += it->second;
    }
    return;
}

void dfs(int u, int p) {
    if (p != -1) {
        colors[u][0] += colors[p][0];
        colors[u][1] += colors[p][1];
        colors[u][2] += colors[p][2];
    }
    int mn = min({colors[u][0], colors[u][1], colors[u][2]});
    colors[u][0] -= mn, colors[u][1] -= mn, colors[u][2] -= mn;
    if (adj[u].size() == 1 && adj[u][0].first == p) {
        st[u][colors[u]]++;
        return;
    }
    vector<int> child;
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i].first, c = adj[u][i].second;
        if (v != p) {
            colors[v][c] += 1;
            dfs(v, u);
            child.push_back(v);
        }
    }
    for (int i = 1; i < child.size(); i++) {
        int a = dsu_find(child[0]), b = dsu_find(child[i]);
        if (a != b) {
            dsu_merge(a, b, colors[u]);
        }
    }
    int a = dsu_find(child[0]);
    auto f = st[a].find(colors[u]);
    if (f != st[a].end()) {
        ans += f->second;
    }
    st[a][colors[u]]++;
    parent[u] = a;
    return;
}

int main() {
    IOS;
    int n;
    cin >> n;
    colors.resize(n, vector<int>(3, 0));
    for (int i = 0; i < n - 1; i++) {
        int u, v, a; char c;
        cin >> u >> v >> c;
        if (c == 'S') {
            a = 0;
        } else if (c == 'I') {
            a = 1;
        } else {
            a = 2;
        }
        u--, v--;
        adj[u].push_back(make_pair(v, a));
        adj[v].push_back(make_pair(u, a));
    }
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
    dfs(0, -1);
    cout << ans;

    return 0;
}
