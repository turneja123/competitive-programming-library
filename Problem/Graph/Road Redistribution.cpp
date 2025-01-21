//https://dmoj.ca/problem/yac9p5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e4 + 5;

set<int> g[N];
set<int> h[N];

int n;
bool exists[N];
bool need[N];
bool vis[N];
bool sp[N];
int color[N];
int parent[N];

vector<int> edges;
vector<int> cycle;

int to_id(int u, int v) {
    if (u > v) {
        swap(u, v);
    }
    return u * n + v;
}

pair<int, int> get_id(int e) {
    return make_pair(e / n, e % n);
}

void dfs_init(int u) {
    vis[u] = true;
    for (int v : h[u]) {
        if (!vis[v]) {
            int e = to_id(u, v);
            sp[e] = true;
            edges.push_back(to_id(u, v));
            dfs_init(v);
        }
    }
}

void dfs(int u, int p) {
    color[u] = 1;
    parent[u] = p;
    for (int v : g[u]) {
        if (color[v] == 0) {
            dfs(v, u);
        } else if (color[v] == 1 && v != p) {
            cycle.push_back(to_id(u, v));
            int x = u;
            while (x != v) {
                cycle.push_back(to_id(x, parent[x]));
                x = parent[x];
            }

        }
        if (cycle.size()) {
            color[u] = 2;
            return;
        }
    }
    color[u] = 2;
    return;
}


int main() {
    IOS;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        int e = to_id(u, v);
        g[u].insert(v);
        g[v].insert(u);
        exists[e] = true;
    }
    for (int i = 0; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        int e = to_id(u, v);
        h[u].insert(v);
        h[v].insert(u);
        need[e] = true;
    }
    dfs_init(0);
    vector<tuple<int, int, int, int>> ans;
    for (int i = 0; i < n - 1; i++) {
        int e = edges[i];
        if (exists[e]) {
            continue;
        }
        tuple<int, int, int, int> cur;
        dfs(0, 0);
        for (int j = 0; j < cycle.size(); j++) {
            if (!sp[cycle[j]]) {
                auto [u, v] = get_id(cycle[j]);
                exists[cycle[j]] = false;
                g[u].erase(v);
                g[v].erase(u);
                get<0>(cur) = u, get<1>(cur) = v;
                break;
            }
        }
        auto [u, v] = get_id(e);
        get<2>(cur) = u, get<3>(cur) = v;
        exists[e] = true;
        g[u].insert(v);
        g[v].insert(u);
        cycle.clear();
        for (int j = 0; j < n; j++) {
            color[j] = 0;
            parent[j] = 0;
        }
        ans.push_back(cur);
    }
    for (int i = 0; i < N; i++) {
        if (need[i] && !exists[i]) {
            int e = i;
            tuple<int, int, int, int> cur;
            dfs(0, 0);
            for (int j = 0; j < cycle.size(); j++) {
                if (!need[cycle[j]]) {
                    auto [u, v] = get_id(cycle[j]);
                    exists[cycle[j]] = false;
                    g[u].erase(v);
                    g[v].erase(u);
                    get<0>(cur) = u, get<1>(cur) = v;
                    break;
                }
            }
            auto [u, v] = get_id(e);
            get<2>(cur) = u, get<3>(cur) = v;
            exists[e] = true;
            g[u].insert(v);
            g[v].insert(u);
            cycle.clear();
            for (int j = 0; j < n; j++) {
                color[j] = 0;
                parent[j] = 0;
            }
            ans.push_back(cur);
        }
    }
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) {
        auto [u, v, x, y] = ans[i];
        cout << u + 1 << " " << v + 1 << " " << x + 1 << " " << y + 1 << endl;
    }
    return 0;
}
