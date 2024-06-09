//https://www.spoj.com/problems/HCMUS20A/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int a[N];
int color[N];
int parent[N];
int up[N];
long long wt[N];
long long dist[N];
vector<int> adj[N];
unordered_map<int, long long> mp[N];
long long ans = -1e12;

int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

void dsu_merge(int a, int b, int p) {
    if (mp[a].size() > mp[b].size()) {
        swap(a, b);
    }
    parent[a] = b;
    for (auto it = mp[a].begin(); it != mp[a].end(); ++it) {
        int x = it->first - ((up[p] == -1) ? 0 : color[up[p]]);
        int y = -x + color[p];
        auto f = mp[b].find(y);
        if (f != mp[b].end()) {
            ans = max(ans, it->second + f->second - dist[p] * 2 + wt[p]);
        }
    }
    for (auto it = mp[a].begin(); it != mp[a].end(); ++it) {
        auto f = mp[b].find(it->first);
        if (f == mp[b].end()) {
            mp[b][it->first] = it->second;
        } else {
            mp[b][it->first] = max(mp[b][it->first], it->second);
        }
    }
    return;
}

void dfs(int u, int p) {
    up[u] = p;
    for (int v : adj[u]) {
        if (v != p) {
            dist[v] = dist[u] + wt[v];
            color[v] = color[u] + a[v];
            dfs(v, u);
        }
    }
    mp[u][color[u]] = dist[u];
    for (int v : adj[u]) {
        if (v != p) {
            int a = dsu_find(u), b = dsu_find(v);
            dsu_merge(a, b, u);
        }
    }
    return;
}

int main() {
    IOS;
    int n;
    cin >> n;
    string s;
    cin >> s;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'B') {
            a[i] = 1;
        } else {
            a[i] = -1;
        }
    }
    for (int i = 0; i < n; i++) {
        cin >> wt[i];
        parent[i] = i;
    }
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        p--;
        adj[p].push_back(i);
        adj[i].push_back(p);
    }
    dist[0] = wt[0];
    color[0] = a[0];
    dfs(0, -1);
    cout << ans;
    return 0;
}
