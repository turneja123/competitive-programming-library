//https://atcoder.jp/contests/abc248/tasks/abc248_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 998244353;

int parent[N];
int depth[N];
int val[N];
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
        for (auto f = mp[b].begin(); f != mp[b].end(); ++f) {
            long long g = __gcd(it->first, f->first);
            ans += ((long long)it->second.second * f->second.first + (long long)f->second.second * it->second.first - (long long)it->second.first * f->second.first * (depth[u]) * 2 + it->second.first * f->second.first + M) % M * g;
        }
    }
    ans %= M;
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
            map<int, pair<int, long long>> nx;
            for (auto it = mp[b].begin(); it != mp[b].end(); ++it) {
                long long g = __gcd(it->first, val[u]);
                auto f = nx.find(g);
                if (f != nx.end()) {
                    f->second.first += it->second.first;
                    f->second.second += it->second.second;
                } else {
                    nx[g] = it->second;
                }
            }
            mp[b] = nx;
            dsu_merge(a, b, u);
        }
    }
    return;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
    dfs(0, -1);
    cout << ans;

    return 0;
}
