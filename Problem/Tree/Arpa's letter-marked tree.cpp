//https://codeforces.com/contest/741/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

vector<pair<int, int>> adj[N];
int parent[N];
gp_hash_table<int, int, custom_hash> mp[N];
int ans[N];
int depth[N];

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
        int x = it->first;
        auto f = mp[b].find(x);
        if (f != mp[b].end()) {
            ans[u] = max(ans[u], it->second + f->second - 2 * depth[u]);
        }
        for (int j = 0; j < 26; j++) {
            auto f = mp[b].find(x ^ (1 << j));
            if (f != mp[b].end()) {
                ans[u] = max(ans[u], it->second + f->second - 2 * depth[u]);
            }
        }
    }
    for (auto it = mp[a].begin(); it != mp[a].end(); ++it) {
        auto f = mp[b].find(it->first);
        if (f == mp[b].end()) {
            mp[b][it->first] = it->second;
        } else {
            f->second = max(f->second, it->second);
        }
    }
    mp[a].clear();
    return;
}

void dfs(int u, int p, int val) {
    for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
        int v = it->first, x = it->second;
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u, val ^ (1 << x));
        }
    }
    mp[u][val] = depth[u];
    for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
        int v = it->first;
        if (v != p) {
            ans[u] = max(ans[u], ans[v]);
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
    for (int i = 1; i < n; i++) {
        int u; char c;
        cin >> u >> c;
        u--;
        adj[u].push_back(make_pair(i, c - 'a'));
        adj[i].push_back(make_pair(u, c - 'a'));
    }
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
    dfs(0, 0, 0);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }


    return 0;
}
