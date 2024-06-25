//https://atcoder.jp/contests/abc359/tasks/abc359_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int val[N];
int parent[N];
int depth[N];
vector<int> adj[N];
map<int, pair<int, long long>> mp[N];

long long ans = 0;

int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

void dsu_merge(int a, int b, int u) {
    if (mp[a].size() > mp[b].size()) {
        swap(a, b);
    }
    parent[a] = b;
    for (auto it = mp[a].begin(); it != mp[a].end(); ++it) {
        auto f = mp[b].find(it->first);
        if (f != mp[b].end()) {
            ans += (long long)it->second.second * f->second.first + (long long)f->second.second * it->second.first - (long long)it->second.first * f->second.first * depth[u] * 2;
        }
    }
    for (auto it = mp[a].begin(); it != mp[a].end(); ++it) {
        auto f = mp[b].find(it->first);
        if (f != mp[b].end()) {
            f->second.first += it->second.first;
            f->second.second += it->second.second;
        } else {
            mp[b][it->first] = it->second;
        }

    }
    return;
}

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }
    mp[u][val[u]] = make_pair(1, depth[u]);
    for (int v : adj[u]) {
        if (v != p) {
            int a = dsu_find(u), b = dsu_find(v);
            if (a != b) {
                dsu_merge(a, b, u);
            }
        }
    }
    return;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        cin >> val[i];
        parent[i] = i;
    }
    dfs(0, -1);
    cout << ans;

    return 0;
}
